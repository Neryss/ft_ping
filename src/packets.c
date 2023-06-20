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

	if ((received_bytes = recvmsg(g_ping.socket, &msg, 0)) == -1) {
		perror("recvmsg");
		exit(1);
	}

	// Process the received packet
	printf("Ping reply received from %s\n", inet_ntoa(addr.sin_addr));
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
	icmp_header.un.echo.sequence = 0;
	icmp_header.checksum = 0;
	icmp_header.checksum = checksum((unsigned short *)&icmp_header, ICMP_HEADER_SIZE);

	// Construct the packet
	memcpy(packet, &icmp_header, ICMP_HEADER_SIZE);
	packet_size = ICMP_HEADER_SIZE;

	// Send the packet
	if (sendto(g_ping.socket, packet, packet_size, 0, (struct sockaddr *)g_ping.res, sizeof(struct sockaddr)) == -1) {
		perror("sendto");
		exit(1);
	}
	printf("Ping sent\n");
}
