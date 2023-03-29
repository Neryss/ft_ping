#include "../include/ping.h"

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

void	ping()
{
	int	msg_count = 0;
	while (g_ping.is_running)
	{
		t_pckt	pckt;
		ft_bzero(&pckt, sizeof(pckt));
		pckt.msg = ft_calloc(g_ping.packet_size-sizeof(struct icmphdr), sizeof(char));
		pckt.icmp.type = ICMP_ECHO;
		pckt.icmp.un.echo.id = getpid();

		for (unsigned int i = 0; i < sizeof(pckt.msg) - 1; i++)
			pckt.msg[i] = i+'0';
		pckt.icmp.un.echo.sequence = msg_count++;
		pckt.icmp.checksum = checksum(&pckt, sizeof(pckt));

		printf("here\n");
		usleep(g_ping.interval);
		free(pckt.msg);
	}
}

int	socketInit()
{
	struct timeval	timeout = {(long)g_ping.interval, 0};
	if (setsockopt(g_ping.socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		ERROR_PRINTF("setting socket option timeout failed\n");
		ftExit(1);
	}
	#ifdef DEBUG
		printf("Socket timeout set\n");
	#endif
	if (setsockopt(g_ping.socket, SOL_IP, IP_TTL, &g_ping.ttl, sizeof(int)) < 0)
	{
		ERROR_PRINTF("setting socket options TTL failed\n");
		ftExit(1);
	}
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
	hints.ai_family = AF_UNSPEC;
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
	printf("ip: %s\n", ip);
	g_ping.ip = ft_strdup(ip);
	g_ping.res = res;
	return (0);
}