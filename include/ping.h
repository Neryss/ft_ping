#ifndef PING_H
#define PING_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../libft/libft.h"
#define ERROR_PRINTF(x) (printf("ping: %s", x))
#define HELP_MSG "\nUsage\n  ping [options] <destination>\n\nOptions:\n  <destination>       dns name or ip address\n"

typedef struct s_params
{
	bool		verbose;
	bool		help;
}				t_params;


int	parseInput(char **argv);

#endif