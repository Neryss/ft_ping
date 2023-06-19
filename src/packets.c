#include "../include/ping.h"
#include <errno.h>

//wtf

unsigned short	checksum(void *b, int len)
{
	unsigned short	*buf = b;
	unsigned int	sum = 0;
	unsigned short	res = 0;

	for (sum = 0; len > 1; len -=2)
		sum += *buf++;
	if (len == 1)
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	res = ~sum;
	return (res);
}


// Error doesn't come from recvmsg, tried with recvfrom but still got the issue
void		receivePacket(void)
{
	char	buff[MAX_PACKET_SIZE];
	// char	control_buffer[MAX_PACKET_SIZE];
	// struct	sockaddr_in addr;
	struct	iovec iov;
	struct	msghdr msg;

	iov.iov_base = buff;
	iov.iov_len = sizeof(buff);
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	// msg.msg_flags = MSG_DONTWAIT;
	// msg.msg_control = control_buffer;
	// msg.msg_controllen = sizeof(control_buffer);

	int	rec = recvmsg(g_ping.socket, &msg, 0);
	if (rec == -1)
	{
		printf("error rec: %d\n", rec);
		printf("errno: %s\n", strerror(errno));
	}
	else
	{
		printf("done\n");
		// printf("ping reply received from %s\n", inet_ntoa(addr.sin_addr));
	}
}

void	sendPacket()
{
	// That seems weird (+ the free later on)
	g_ping.pckt.msg = ft_calloc(g_ping.packet_size, sizeof(char));
	g_ping.pckt.ip.ip_v = 4;
	g_ping.pckt.ip.ip_p = IPPROTO_ICMP;
	g_ping.pckt.icmp.type = ICMP_ECHO;
	g_ping.pckt.icmp.code = 0;
	g_ping.pckt.icmp.un.echo.id = getpid();
	g_ping.pckt.icmp.un.echo.sequence = g_ping.seq++;
	g_ping.pckt.icmp.checksum = 0;
	g_ping.pckt.ip.ip_ttl = g_ping.ttl;
	// TODO: fix error on google.com/riot.de etc
	gettimeofday(&g_ping.start, NULL);
	g_ping.pckt.icmp.checksum = checksum(&g_ping.pckt, sizeof(g_ping.pckt));
	if (sendto(g_ping.socket, &g_ping.pckt, g_ping.packet_size, 0, (struct sockaddr *)g_ping.res, sizeof(struct sockaddr)) <= 0)
	{
		// DEBUG
		printf("errno: %s\n", strerror(errno));
		printf("failed to send packet\n");
		ftExit(1);
	}
	printf("time: %ld\n", g_ping.start.tv_usec);
	free(g_ping.pckt.msg);
}
