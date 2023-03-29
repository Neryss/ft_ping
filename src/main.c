#include "../include/ping.h"

t_ping g_ping;

int	main(int argc, char **argv)
{
	checkRoot();
	parseInput(argc, argv);
	dnsLookup();
	if ((g_ping.socket = socket(g_ping.res->ai_family, SOCK_RAW, g_ping.res->ai_family == AF_INET ? IPPROTO_ICMP : IPPROTO_ICMPV6)) < 0)
	{
		printf("Error: sock file descriptor not received\n");
		ftExit(1);
	}
	printf("sock file descriptor %d received\n", g_ping.socket);
	socketInit();
	// ping();
	signal(SIGINT, intHandler);
	ping();
	#ifdef DEBUG
		printParams();
	#endif
	close(g_ping.socket);
	ftExit(0);
}