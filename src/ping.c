#include "../include/ping.h"

int	reverseDnsLookup()
{
	//todo
	return (0);
}

void	ping()
{
	while (g_ping.is_running)
	{
		sendPacket();
		alarm(1);
		printf("here\n");
		receivePacket();
	}
}

int	socketInit()
{
	struct timeval	timeout = {(long)g_ping.interval, 0};
	// int	opt_val = 1;
	if ((g_ping.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("Error: sock file descriptor not received\n");
		ftExit(1);
	}
	printf("sock file descriptor %d received\n", g_ping.socket);
	// Set timeout option (how many seconds until answer)
	// if (setsockopt(g_ping.socket, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
	// {
	// 	ERROR_PRINTF("setting socket option timeout failed\n");
	// 	ftExit(1);
	// }
	// If this isn't present it causes a hang
	if (setsockopt(g_ping.socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		ERROR_PRINTF("setting socket option timeout failed\n");
		ftExit(1);
	}
	if (setsockopt(g_ping.socket, SOL_IP, IP_TTL, &g_ping.ttl, sizeof(int)) < 0)
	{
		ERROR_PRINTF("setting socket options TTL failed\n");
		ftExit(1);
	}
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