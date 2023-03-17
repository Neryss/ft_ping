#include "../include/ping.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (0);
	}
	return (0);
}