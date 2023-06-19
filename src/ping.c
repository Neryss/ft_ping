#include "../include/ping.h"
#include <errno.h>

int	reverseDnsLookup()
{
	//todo
	return (0);
}

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

void	sendPacket(int seq)
{
	// That seems weird (+ the free later on)
	g_ping.pckt.msg = ft_calloc(g_ping.packet_size, sizeof(char));
	g_ping.pckt.icmp.type = ICMP_ECHO;
	g_ping.pckt.icmp.code = 0;
	g_ping.pckt.icmp.un.echo.id = getpid();
	g_ping.pckt.icmp.un.echo.sequence = seq++;
	g_ping.pckt.icmp.checksum = checksum(&g_ping.pckt, sizeof(g_ping.pckt));
	g_ping.pckt.ip.ip_ttl = g_ping.ttl;
	// TODO: fix error on google.com/riot.de etc
	gettimeofday(&g_ping.start, NULL);
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

int		receivePacket(void)
{
	char	buff[MAX_PACKET_SIZE];
	char	control_buffer[MAX_PACKET_SIZE];
	struct	sockaddr_in addr;
	struct	iovec iov;
	struct	msghdr msg;

	iov.iov_base = buff;
	iov.iov_len = sizeof(buff);
	msg.msg_name = &addr;
	msg.msg_namelen = sizeof(addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = control_buffer;
	msg.msg_controllen = sizeof(control_buffer);

	int	rec = recvmsg(g_ping.socket, &msg, 0);
	if (rec == -1)
	{
		printf("error rec: %d\n", rec);
		printf("errno: %s\n", strerror(errno));
	}
	else
		printf("ping reply received from %s\n", inet_ntoa(addr.sin_addr));
	return (0);
}

void	ping()
{
	int	sent = 0;
	while (sent < g_ping.timeout && g_ping.is_running)
	{
		sendPacket(sent);
		// alarm(1);
		printf("here\n");
		receivePacket();
	}
}

int	socketInit()
{
	struct timeval	timeout = {(long)g_ping.interval, 0};
	int	opt_val = 1;
	if ((g_ping.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("Error: sock file descriptor not received\n");
		ftExit(1);
	}
	printf("sock file descriptor %d received\n", g_ping.socket);
	if (setsockopt(g_ping.socket, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
	{
		ERROR_PRINTF("setting socket option timeout failed\n");
		ftExit(1);
	}
	if (setsockopt(g_ping.socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		ERROR_PRINTF("setting socket option timeout failed\n");
		ftExit(1);
	}
	// #ifdef DEBUG
	// 	printf("Socket timeout set\n");
	// #endif
	// if (setsockopt(g_ping.socket, SOL_IP, IP_TTL, &g_ping.ttl, sizeof(int)) < 0)
	// {
	// 	ERROR_PRINTF("setting socket options TTL failed\n");
	// 	ftExit(1);
	// }
	#ifdef DEBUG
		printf("Socket ttl set\n");
	#endif
	return(0);
}

int	dnsLookup()
{
	struct addrinfo	hints;
	struct addrinfo	*res = NULL;
	int				error = 0;

	ft_memset(&hints, 0, sizeof(hints));
	// TODO: fix AF_UNSPEC network unreachable on google.com etc
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_CANONNAME;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	error = getaddrinfo(g_ping.destination, NULL, &hints, &res);
	if (error)
	{
		printf("Error in addrinfo\n");
		ftExit(1);
	}
	char ip[50] = "";
	inet_ntop(res->ai_addr->sa_family, &res->ai_addr->sa_data[2], ip, sizeof(ip));
	if (res->ai_family == AF_INET)
		printf("AF_INET\n");
	else
		printf("IPV6\n");
	printf("ip: %s\n", ip);
	g_ping.ip = ft_strdup(ip);
	g_ping.res = res;
	return (0);
}