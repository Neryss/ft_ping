#include "../include/ping.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (0);
	}
	for (int i = 1; i < argc; i++)
		printf("%s\n", argv[i]);
	return (0);
}