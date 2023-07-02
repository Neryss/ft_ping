#include "../include/ping.h"

void	initParams()
{
	g_ping.destination = NULL;
	g_ping.socket = 0;
	g_ping.is_running = true;
	g_ping.ttl = 32;
	g_ping.interval = 1;
	g_ping.timeout = 4;
	g_ping.packet_size = 48;
	g_ping.count = -1;
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
	g_ping.seq = 0;
	g_ping.sent = 0;
	g_ping.errors = 0;
	g_ping.received = 0;
	g_ping.ready = true;
	g_ping.time.max = 0;
	g_ping.time.min = 0;
	g_ping.time.avg = 0;
	g_ping.time.rtt = 0;
	g_ping.time.sqrd = 0;
	clock_gettime(CLOCK_MONOTONIC, &g_ping.ts_s);
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
	printf("ttl:         %d\n", g_ping.ttl);
	printf("size:        %d\n", g_ping.packet_size);
	printf("count:       %d\n", g_ping.count);
}

static int	checkSocket()
{
	int	error = 0;
	socklen_t	len = sizeof(error);

	if (setsockopt(g_ping.socket, SOL_SOCKET, SO_ERROR, &error, len))
		return (1);
	if (error)
		return (1);
	return (0);
}

void	ftExit(int code)
{
	if (g_ping.destination)
		free(g_ping.destination);
	if (checkSocket())
		close (g_ping.socket);
	if (g_ping.res)
		freeaddrinfo(g_ping.res);
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

void	intHandler()
{
	g_ping.is_running = false;
	displayStats();
}

void	catcher(int signum)
{
	g_ping.ready = true;
	(void)signum;
}

#include <math.h>
void	displayStats()
{
	double long		mdev;
	double			loss;

	g_ping.time.avg /= g_ping.sent;
	struct timespec	ts_end;
	clock_gettime(CLOCK_MONOTONIC, &ts_end);
	double timeElapsed = ((double)(ts_end.tv_nsec -
								   g_ping.ts_s.tv_nsec)) /
						 1000000.0;
	long double total_msec = (ts_end.tv_sec - g_ping.ts_s.tv_sec) * 1000.0 + timeElapsed;
	loss = (g_ping.sent - g_ping.received) / g_ping.sent * 100.0;
	// called mdev but it's the standart derivation
	mdev = sqrt((g_ping.time.sqrd / g_ping.sent) - (g_ping.time.avg * g_ping.time.avg));
	printf("--- %s ping statistics ---\n", g_ping.destination);
	if (!g_ping.errors)
		printf("%.0f packets transmitted, %.0f received, %.0f%% packet loss, time: %.0Lf ms\n", g_ping.sent, g_ping.received, loss, total_msec);
	else
		printf("%.0f packets transmitted, %.0f received, +%.0f errors, %.0f%% packet loss, time: %.0Lf ms\n", g_ping.sent, g_ping.received, g_ping.errors, loss, total_msec);
	printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", g_ping.time.min, g_ping.time.avg, g_ping.time.max, mdev);
}