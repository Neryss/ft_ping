#include "../include/ping.h"

int	reverseDnsLookup()
{
	//todo
	return (0);
}

void	sendPing()
{
	
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

void	sendPing()
{
	
	// if (setsockopt(g_ping.socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&g_ping.timeout, sizeof(g_ping.timeout)))
	// {
	// 	ERROR_PRINTF("setting socket options timeout failed\n");
	// 	return ;
	// }
	// #ifdef DEBUG
	// 	printf("Socket timeout set\n");
	// #endif
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