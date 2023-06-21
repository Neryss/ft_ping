#include "../include/ping.h"
#include <errno.h>

//wtf

unsigned short checksum(void *b, int len) {
	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

void		receivePacket(void)
{
	char buffer[MAX_PACKET_SIZE];
	struct sockaddr_in addr;
	struct iovec iov;
	struct msghdr msg;
	char control_buffer[MAX_PACKET_SIZE];
	int received_bytes;

	iov.iov_base = buffer;
	iov.iov_len = sizeof(buffer);

	msg.msg_name = &addr;
	msg.msg_namelen = sizeof(addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = control_buffer;
	msg.msg_controllen = sizeof(control_buffer);

	if ((received_bytes = recvmsg(g_ping.socket, &msg, 0)) < 0) {
		ERROR_PRINTF("recvmsg\n");
		ftExit(1);
	}
	if (gettimeofday(&g_ping.end, NULL) < 0)
	{
		ERROR_PRINTF("gettimeofday error\n");
		ftExit(1);
	}
	char	tmp[50];
	inet_ntop(AF_INET, &addr.sin_addr, tmp, 100);
	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2fms\n", received_bytes, g_ping.destination, tmp, g_ping.seq, g_ping.ttl, (double)(g_ping.end.tv_usec - g_ping.start.tv_usec)/1000);
}
#define ICMP_HEADER_SIZE sizeof(struct icmphdr)
void	sendPacket()
{
	struct icmphdr icmp_header;
	char packet[MAX_PACKET_SIZE];
	int packet_size;

	// Prepare ICMP header
	icmp_header.type = ICMP_ECHO;
	icmp_header.code = 0;
	icmp_header.un.echo.id = getpid();
	icmp_header.un.echo.sequence = g_ping.seq++;
	icmp_header.checksum = 0;
	icmp_header.checksum = checksum((unsigned short *)&icmp_header, ICMP_HEADER_SIZE);

	// Construct the packet
	memcpy(packet, &icmp_header, ICMP_HEADER_SIZE);
	packet_size = ICMP_HEADER_SIZE;

	// Send the packet
	if (gettimeofday(&g_ping.start, NULL) < 0)
	{
		ERROR_PRINTF("gettimeofday error\n");
		ftExit(1);
	}
	// printf("sent at: %ld\n", g_ping.start.tv_usec);
	if (sendto(g_ping.socket, packet, packet_size, 0, (struct sockaddr *)g_ping.res->ai_addr, sizeof(struct sockaddr)) == -1) {
		perror("sendto");
		ftExit(1);
	}
	// printf("Ping sent\n");
	g_ping.ready = false;
}
