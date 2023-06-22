#include "../include/ping.h"

int	parseInput(int argc, char **argv)
{
	bool args = false;
	bool ttl = false;
	bool count = false;
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
		// printf("scan: [%c]\n", argv[i][k]);
		if (argv[i][k++] == '-')
		{
			// printf("help: [%c]\n", argv[i][k]);
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
				// check if size is formated correctly (can be -s<size> or -s <size>)
				else if (argv[i][k] == 's')
				{
					if (!argv[i][k + 1])
						args = true;
					else
						g_ping.packet_size = ft_atoi(argv[i] + 2);
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 't')
				{
					if (!argv[i][k + 1])
						ttl = true;
					else
						g_ping.ttl = ft_atoi(argv[i] + 2);
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 'c')
				{
					if (!argv[i][k + 1])
						count = true;
					else
						g_ping.count = ft_atoi(argv[i] + 2);
					while (argv[i][k])
						k++;
				}
				else
				{
					printf("invalid option -- \'%c\'\n", argv[i][k]);
					printf(HELP_MSG);
					ftExit(1);
				}
				if (argv[i][k])
					k++;
			}
		}
		else if (args || ttl || count)
		{
			if (!ft_isalnum(argv[i][k]))
			{
				printf("invalid argument: %s\n", argv[i]);
				ftExit(-1);
			}
			if (args)
				g_ping.packet_size = ft_atoi(argv[i]);
			else if (ttl)
				g_ping.ttl = ft_atoi(argv[i]);
			else if (count)
				g_ping.count = ft_atoi(argv[i]);
			args = false;
			ttl = false;
			count = false;
		}
		else if (!g_ping.destination)
		{
			if (!(g_ping.destination = ft_strdup(argv[i])))
				ftExit(-1);
			if (dnsLookup())
			{
				printf("%s: No address associated with hostname\n", g_ping.destination);
				ftExit(-1);
			}
			inet_ntop(AF_INET, &(((struct sockaddr_in *)g_ping.res->ai_addr)->sin_addr), g_ping.ip, INET_ADDRSTRLEN);
			printf("PING: %s (%s) %d(%ld) bytes of data.\n", g_ping.destination, g_ping.ip, g_ping.packet_size + 8, g_ping.packet_size + 8 + sizeof(struct iphdr));
		}
		else if (ft_isalnum(argv[i][k]))
		{
			printf("bad argument\n");
			ftExit(-1);
		}
		i++;
	}
	return (0);
}