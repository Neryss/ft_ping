#include "../include/ping.h"

/*
// loops until signal or out of count in case of -c
*/

void	ping()
{
	gettimeofday(&g_ping.command_time, NULL);
	while (g_ping.is_running)
	{
		if (g_ping.seq >= g_ping.count && g_ping.count >= 0)
		{
			displayStats();
			ftExit(0);
		}
		if (g_ping.ready)
		{
			if (g_ping.flags.a_flag)
				printf("\a");
			sendPacket();
			alarm(g_ping.interval);
			receivePacket();
		}
	}
}

/*
// Create a socket and set several options for timeout and time to live
*/

int	socketInit()
{
	struct timeval	timeout = {(long)g_ping.timeout, 0};
	if ((g_ping.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("Error: sock file descriptor not received\n");
		ftExit(1);
	}
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

/*
// check for ip address
*/

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