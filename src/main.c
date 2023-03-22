#include "../include/ping.h"

t_params g_params;

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	initParams();
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (0);
	}
	parseInput(argv);
	dnsLookup();
	// reverseDnsLookup();
	#ifdef DEBUG
		printParams();
	#endif
	return (cleanup());
}