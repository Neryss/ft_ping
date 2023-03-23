#include "../include/ping.h"

t_ping g_ping;

int	main(int argc, char **argv)
{
	if (checkRoot())
		return (1);
	initParams();
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (1);
	}
	parseInput(argv);
	dnsLookup();
	if ((g_ping.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) < 0))
	{
		printf("Error: sock file descriptor not received\n");
		return (cleanup());
	}
	printf("sock file descriptor %d received\n", g_ping.socket);
	#ifdef DEBUG
		printParams();
	#endif
	close(g_ping.socket);
	return (cleanup());
}