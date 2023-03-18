#include "../include/ping.h"

void	initParams()
{
	g_params.v_flag = false;
	g_params.f_flag = false;
	g_params.m_flag = false;
	g_params.l_flag = false;
	g_params.I_flag = false;
	g_params.M_flag = false;
	g_params.n_flag = false;
	g_params.w_flag = false;
	g_params.W_flag = false;
	g_params.a_flag = false;
	g_params.D_flag = false;
	g_params.t_flag = false;
}

void	printParams()
{
	printf("[===PARAMS===]\n");
	printf("verbose:   %d\n", g_params.v_flag);
	printf("flood:     %d\n", g_params.f_flag);
	printf("mark:      %d\n", g_params.m_flag);
	printf("preload:   %d\n", g_params.l_flag);
	printf("interface: %d\n", g_params.I_flag);
	printf("mtu:       %d\n", g_params.M_flag);
	printf("no dns:    %d\n", g_params.n_flag);
	printf("deadline:  %d\n", g_params.w_flag);
	printf("timeout:   %d\n", g_params.W_flag);
	printf("audible:   %d\n", g_params.a_flag);
	printf("timestamp: %d\n", g_params.D_flag);
	printf("ttl:       %d\n", g_params.t_flag);
}