#include "../include/ping.h"

void	initParams()
{
	g_ping.destination = NULL;
	g_ping.socket = 0;
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

int		cleanup()
{
	if (g_ping.destination)
		free(g_ping.destination);
	if (g_ping.ip)
		free(g_ping.ip);
	if (g_ping.socket)
		close(g_ping.socket);
	return (0);
}