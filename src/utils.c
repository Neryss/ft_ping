#include "../include/ping.h"

void	initParams()
{
	g_ping.destination = NULL;
	g_ping.socket = 0;
	g_ping.is_running = true;
	g_ping.ttl = 64;
	g_ping.interval = 1000000;
	g_ping.timeout = 4;
	g_ping.packet_size = 64;
	g_ping.flags.v_flag = false;
	g_ping.flags.f_flag = false;
	g_ping.flags.m_flag = false;
	g_ping.flags.l_flag = false;
	g_ping.flags.I_flag = false;
	g_ping.flags.M_flag = false;
	g_ping.flags.n_flag = false;
	g_ping.flags.w_flag = false;
	g_ping.flags.W_flag = false;
	g_ping.flags.a_flag = false;
	g_ping.flags.D_flag = false;
	g_ping.flags.t_flag = false;
}

void	printParams()
{
	printf("[===PARAMS===]\n");
	printf("destination: %s\n", g_ping.destination);
	printf("verbose:     %d\n", g_ping.flags.v_flag);
	printf("flood:       %d\n", g_ping.flags.f_flag);
	printf("mark:        %d\n", g_ping.flags.m_flag);
	printf("preload:     %d\n", g_ping.flags.l_flag);
	printf("interface:   %d\n", g_ping.flags.I_flag);
	printf("mtu:         %d\n", g_ping.flags.M_flag);
	printf("no dns:      %d\n", g_ping.flags.n_flag);
	printf("deadline:    %d\n", g_ping.flags.w_flag);
	printf("timeout:     %d\n", g_ping.flags.W_flag);
	printf("audible:     %d\n", g_ping.flags.a_flag);
	printf("timestamp:   %d\n", g_ping.flags.D_flag);
	printf("ttl:         %d\n", g_ping.flags.t_flag);
}

#include <fcntl.h>

void	ftExit(int code)
{
	if (g_ping.destination)
		free(g_ping.destination);
	if (g_ping.ip)
		free(g_ping.ip);
	if (fcntl(g_ping.socket, F_GETFD))
		close (g_ping.socket);
	if (g_ping.res)
		freeaddrinfo(g_ping.res);
	printf("exit\n");
	exit(code);
}

int	checkRoot()
{
	if (getuid() != 0)
	{
		ERROR_PRINTF("you must be root to run this program, try with sudo\n");
		ftExit(1);
	}
	return (0);
}

void	intHandler(int sig)
{
	if (sig == SIGINT)
		g_ping.is_running = false;
}