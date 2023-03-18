#include "../include/ping.h"

int	parseInput(char **argv)
{
	int	i = 1;
	while (argv[i])
	{
		int	k = 0;
		if (argv[i][k++] == '-')
		{
			while (argv[i][k])
			{
				if (argv[i][k] == 'h')
				{
					printf(HELP_MSG);
					return (1);
				}
				else if (argv[i][k] == 'v')
					g_params.v_flag = true;
				k++;
			}
		}
		i++;
	}
	return (0);
}