#include "../include/ping.h"

int	parseInput(int argc, char **argv)
{
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		ftExit(1);
	}
	initParams();
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
					ftExit(1);
				}
				else if (argv[i][k] == 'v')
					g_ping.flags.v_flag = true;
				else if (argv[i][k] == 'f')
					g_ping.flags.f_flag = true;
				else if (argv[i][k] == 'n')
					g_ping.flags.n_flag = true;
				else if (argv[i][k] == 'a')
					g_ping.flags.a_flag = true;
				else if (argv[i][k] == 'D')
					g_ping.flags.D_flag = true;
				else
				{
					printf("invalid option -- \'%c\'\n", argv[i][k]);
					printf(HELP_MSG);
					ftExit(1);
				}
				k++;
			}
		}
		else
		{
			printf("aled : %s\n", argv[i]);
			if (!(g_ping.destination = ft_strdup(argv[i])))
				ftExit(-1);
		}
		i++;
	}
	return (0);
}