#include "../include/ping.h"

t_ping g_ping;

int	main(int argc, char **argv)
{
	if (checkRoot())
		return (1);
	if (parseInput(argc, argv))
		return(0);
	dnsLookup();
	if ((g_ping.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) < 0))
	{
		printf("Error: sock file descriptor not received\n");
		return (cleanup());
	}
	signal(SIGINT, intHandler);
	printf("sock file descriptor %d received\n", g_ping.socket);
	#ifdef DEBUG
		printParams();
	#endif
	close(g_ping.socket);
	return (cleanup());
}