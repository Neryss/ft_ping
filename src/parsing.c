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
				else if (argv[i][k] == 'f')
					g_params.f_flag = true;
				else if (argv[i][k] == 'n')
					g_params.n_flag = true;
				else if (argv[i][k] == 'a')
					g_params.a_flag = true;
				else if (argv[i][k] == 'D')
					g_params.D_flag = true;
				else
				{
					printf("invalid option -- \'%c\'\n", argv[i][k]);
					printf(HELP_MSG);
					return (1);
				}
				k++;
			}
		}
		else
		{
			printf("aled : %s\n", argv[i]);
			if (!(g_params.destination = ft_strdup(argv[i])))
				return (-1);
		}
		i++;
	}
	return (0);
}