#include "../include/ping.h"

t_params g_params;

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
	g_params.T_flag = false;
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		ERROR_PRINTF("usage error: Destination address required\n");
		return (0);
	}
	parseInput(argv);
	#ifdef DEBUG
		printParams();
	#endif
	return (0);
}