#include "../include/ping.h"

static void	badArgument(char *argv)
{
	printf("ping: invalid argument: \'%s\'\n", argv);
	ftExit(1);
}

typedef	struct s_bool
{
	bool args;
	bool ttl;
	bool count;
	bool timeout;
	bool interval;
}			t_bool;

static void	handleSpaceArgs(char *argv, t_bool *flags, int k)
{
	if (!ft_isalnum(argv[k]))
	{
		printf("invalid argument: %s\n", argv);
		ftExit(-1);
	}
	if (flags->args)
	{
		if (!ft_islinenum(argv + 2))
			badArgument(argv);
		g_ping.packet_size = ft_atoi(argv);
	}
	else if (flags->ttl)
	{
		if (!ft_islinenum(argv + 2))
			badArgument(argv);
		g_ping.ttl = ft_atoi(argv);
	}
	else if (flags->count)
	{
		if (!ft_islinenum(argv + 2))
			badArgument(argv);
		g_ping.count = ft_atoi(argv);
	}
	else if (flags->timeout)
	{
		if (!ft_islinenum(argv + 2))
			badArgument(argv);
		g_ping.timeout = ft_atoi(argv);
	}
	else if (flags->interval)
	{
		if (!ft_islinenum(argv + 2))
			badArgument(argv);
		g_ping.interval = ft_atoi(argv);
	}
	flags->args = false;
	flags->ttl = false;
	flags->count = false;
	flags->timeout = false;
	flags->interval = false;
}

static void	init_flags(t_bool *flags)
{
	flags->args = false;
	flags->ttl = false;
	flags->count = false;
	flags->timeout = false;
	flags->interval = false;
}

int parseInput(int argc, char **argv)
{
	t_bool	flags;
	init_flags(&flags);
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		ftExit(1);
	}
	initParams();
	int i = 1;
	while (argv[i])
	{
		int k = 0;
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
						flags.args = true;
					else
					{
						if (!ft_islinenum(argv[i] + 2))
							badArgument(argv[i]);
						g_ping.packet_size = ft_atoi(argv[i] + 2);
					}
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 't')
				{
					if (!argv[i][k + 1])
						flags.ttl = true;
					else
					{
						if (!ft_islinenum(argv[i] + 2))
							badArgument(argv[i]);
						g_ping.ttl = ft_atoi(argv[i] + 2);
					}
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 'c')
				{
					if (!argv[i][k + 1])
						flags.count = true;
					else
					{
						if (!ft_islinenum(argv[i] + 2))
							badArgument(argv[i]);
						g_ping.count = ft_atoi(argv[i] + 2);
					}
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 'W')
				{
					if (!argv[i][k + 1])
						flags.timeout = true;
					else
					{
						if (!ft_islinenum(argv[i] + 2))
							badArgument(argv[i]);
						g_ping.timeout = ft_atoi(argv[i] + 2);
					}
					while (argv[i][k])
						k++;
				}
				else if (argv[i][k] == 'i')
				{
					if (!argv[i][k + 1])
						flags.interval = true;
					else
					{
						if (!ft_islinenum(argv[i] + 2))
							badArgument(argv[i]);
						g_ping.interval = ft_atoi(argv[i] + 2);
					}
					while (argv[i][k])
						k++;
				}
				else
				{
					printf("invalid option -- \'%c\'\n", argv[i][k]);
					printf(HELP_MSG);
					badArgument(argv[i]);
				}
				if (argv[i][k])
					k++;
			}
		}
		else if (flags.args || flags.ttl || flags.count || flags.timeout || flags.interval)
		{
			handleSpaceArgs(argv[i], &flags, k);
		}
		else if (!g_ping.destination)
		{
			if (!(g_ping.destination = ft_strdup(argv[i])))
				ftExit(-1);
			printf("Dest: %s\n", g_ping.destination);
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
	if (!g_ping.destination)
	{
		printf("ping: usage error: Destination address required\n");
		ftExit(1);
	}
	return (0);
}