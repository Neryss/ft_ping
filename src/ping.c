#include "../include/ping.h"

int	reverseDnsLookup()
{
	//todo
	return (0);
}

void	sendPing()
{
	if (setsockopt(g_ping.socket, SOL_IP, IP_TTL, g_ping.ttl, sizeof(g_ping.ttl)))
	{
		ERROR_PRINTF("setting socket options TTL failed\n");
		return ;
	}
	#ifdef DEBUG
		printf("Socket ttl set\n");
	#endif
	if (setsockopt(g_ping.socket, SOL_SOCKET, SO_RCVTIMEO, g_ping.timeout, sizeof(g_ping.timeout)))
	{
		ERROR_PRINTF("setting socket options timeout failed\n");
		return ;
	}
	#ifdef DEBUG
		printf("Socket timeout set\n");
	#endif

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
		return (1);
	}
	char ip[50] = "";
	inet_ntop(AF_INET, &res->ai_addr->sa_data[2], ip, sizeof(ip));
	printf("ip: %s\n", ip);
	g_ping.ip = ft_strdup(ip);

	freeaddrinfo(res);
	return (0);
}