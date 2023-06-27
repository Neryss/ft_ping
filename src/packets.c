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

void		rttStats()
{
	long double	rtt;
	rtt = (g_ping.end.tv_usec - g_ping.start.tv_usec) / 1000000.0;
	rtt += g_ping.end.tv_sec - g_ping.start.tv_sec;
	rtt *= 1000.0;
	if (rtt > g_ping.time.max)
		g_ping.time.max = rtt;
	if (rtt < g_ping.time.min || g_ping.time.min == 0.0)
		g_ping.time.min = rtt;
	g_ping.time.rtt = rtt;
	g_ping.time.avg += rtt;
	g_ping.time.sqrd += rtt * rtt;
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

	int	error = 0;

	if ((received_bytes = recvmsg(g_ping.socket, &msg, 0)) < 0) {
		ERROR_PRINTF("recvmsg\n");
	}
	if (received_bytes)
	{
		// TODO: check received packets
		// Convert buffer to IPV4 hdr since it's the first part of it, then ICMP hdr
		struct ip *ip_hdr = (struct ip*)buffer;
		if (ip_hdr->ip_p == IPPROTO_ICMP)
		{
			struct	icmphdr	*content;
			int				icmp_offset = ip_hdr->ip_hl * 4;

			content = (struct icmphdr *)(buffer + icmp_offset);
			if (content->type == 11)
				error = 11;
		}
		g_ping.received++;
	}
	if (gettimeofday(&g_ping.end, NULL) < 0)
	{
		ERROR_PRINTF("gettimeofday error\n");
		ftExit(1);
	}
	char	tmp[50];
	if (g_ping.flags.D_flag)
		printf("[%d.%06d] ", (int)g_ping.end.tv_sec, (int)g_ping.end.tv_usec);
	inet_ntop(AF_INET, &addr.sin_addr, tmp, 100);
	rttStats();
	if (!error)
		printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2Lfms\n", received_bytes, g_ping.destination, tmp, g_ping.seq, g_ping.ttl, g_ping.time.rtt);
	else if (error == 11)
		printf("%d bytes from %s (%s): icmp_seq=%d Time to live exceeded\n", received_bytes, g_ping.destination, tmp, g_ping.seq);
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

	//TODO: generate timestamp
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
	g_ping.sent > 1 ? gettimeofday(&g_ping.command_time, NULL) : 0;
	g_ping.sent++;
	g_ping.ready = false;
}
