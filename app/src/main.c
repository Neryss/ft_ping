#include "../include/ping.h"

t_ping g_ping;

int	main(int argc, char **argv)
{
	checkRoot();
	parseInput(argc, argv);
	socketInit();
	signal(SIGINT, intHandler);
	signal(SIGALRM, catcher);
	ping();
	close(g_ping.socket);
	ftExit(0);
}