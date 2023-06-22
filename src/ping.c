#include "../include/ping.h"

void	ping()
{
	printf("PING ");
	while (g_ping.is_running)
	{
		if (g_ping.seq >= g_ping.count)
			ftExit(0);
		if (g_ping.ready)
		{
			sendPacket();
			alarm(1);
			receivePacket();
		}
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
	// doesn't work
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
	struct addrinfo hints;
	struct addrinfo *result;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(g_ping.destination, NULL, &hints, &result) != 0)
		return (1);
	g_ping.res = (struct addrinfo *)result;
	return (0);
}