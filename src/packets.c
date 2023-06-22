#include "../include/ping.h"
#include <errno.h>

//wtf

void	setPacketSize(char *size)
{
	printf("size: %s\n", size);
	g_ping.packet_size = ft_atoi(size);
	printf("packetsize: %d\n", g_ping.packet_size);
}

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
	}
	if (received_bytes)
		g_ping.received++;
	if (gettimeofday(&g_ping.end, NULL) < 0)
	{
		ERROR_PRINTF("gettimeofday error\n");
		ftExit(1);
	}
	char	tmp[50];
	inet_ntop(AF_INET, &addr.sin_addr, tmp, 100);
	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2fms\n", received_bytes, g_ping.destination, tmp, g_ping.seq, g_ping.ttl, (double)(g_ping.end.tv_usec - g_ping.start.tv_usec)/1000);
}

struct pckt
{
	struct	icmphdr icmp_header;
	char	msg[MAX_PACKET_SIZE];
};

void	sendPacket()
{
	struct pckt	t_packet;
	ft_bzero(&t_packet, sizeof(struct pckt));

	// Prepare ICMP header
	t_packet.icmp_header.type = ICMP_ECHO;
	t_packet.icmp_header.code = 0;
	t_packet.icmp_header.un.echo.id = getpid();
	t_packet.icmp_header.un.echo.sequence = g_ping.seq++;
	for (size_t i = 0; i < (size_t)g_ping.packet_size; i++)
		t_packet.msg[i] = i+'0';
	// printf("payload: %s\n", t_packet.msg);
	t_packet.icmp_header.checksum = 0;
	t_packet.icmp_header.checksum = checksum(&t_packet, g_ping.packet_size + sizeof(struct icmphdr));

	// Send the packet
	if (gettimeofday(&g_ping.start, NULL) < 0)
	{
		ERROR_PRINTF("gettimeofday error\n");
		ftExit(1);
	}
	// printf("sent at: %ld\n", g_ping.start.tv_usec);
	if (sendto(g_ping.socket, &t_packet, g_ping.packet_size + sizeof(struct icmphdr), 0, (struct sockaddr *)g_ping.res->ai_addr, sizeof(struct sockaddr)) == -1) {
		perror("sendto");
		ftExit(1);
	}
	g_ping.sent++;
	// printf("Ping sent\n");
	g_ping.ready = false;
}
