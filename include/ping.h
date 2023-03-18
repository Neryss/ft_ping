#ifndef PING_H
#define PING_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define ERROR_PRINTF(x) (printf("ping: %s", x))
int	parseInput(char **argv);

#endif