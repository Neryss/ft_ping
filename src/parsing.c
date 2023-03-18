#include "../include/ping.h"

int	parseInput(char **argv)
{
	int	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'h')
			{
				printf(HELP_MSG);
				return (1);
			}
			else if (argv[i][1] == 'v')
				g_params.verbose = true;
		}
		i++;
	}
	return (0);
}