#include "../include/ping.h"

t_params g_params;



int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (0);
	}
	parseInput(argv);
	#ifdef DEBUG
		printParams();
	#endif
	return (0);
}