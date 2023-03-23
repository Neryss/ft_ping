#ifndef PING_H
#define PING_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include "../libft/libft.h"
#define ERROR_PRINTF(x) (printf("ping: %s", x))
#define HELP_MSG "\nUsage\n  ping [options] <destination>\n\nOptions:\n  <destination>      dns name or ip address\n\
	-h                 print help and exit\n\
	-v                 verbose output (TODO)\n\
	-f                 flood ping (TODO)\n\
	-m <mark>          tag the packets going out (TODO)\n\
	-l <preload>       send <preload> number of packages while waiting replies (TODO)\n\
	-I <interface>     either interface name or address (TODO)\n\
	-M <opts>          define mtu discovery, can be one of <do|dont|want> (TODO)\n\
	-n                 no dns name resolution (TODO)\n\
	-w <deadline>      reply wait <deadline> in seconds (TODO)\n\
	-W <timeout>       time to wait for response (TODO)\n\
	-a                 use audible ping (TODO)\n\
	-D                 print timestamps (TODO)\n\
	-t <ttl>           define time to live (TODO)\n"

typedef struct s_ping_flags
{
	bool		v_flag;	// verbose output
	bool		f_flag;	// flood ping (TODO)
	bool		m_flag;	// <mark> tag the packets going out (TODO)
	bool		l_flag;	// send <preload> number of packages while waiting replies (TODO)
	bool		I_flag;	// <interface> either interface name or address (TODO)
	bool		M_flag;	// <opts> define mtu discovery, can be one of <do|dont|want> (TODO)
	bool		n_flag;	// no dns name resolution (TODO)
	bool		w_flag;	// <deadline> reply wait <deadline> in seconds (TODO)
	bool		W_flag;	// <timeout> time to wait for response (TODO)
	bool		a_flag;	// use audible ping (TODO ez)
	bool		D_flag;	// print timestamps (TODO)
	bool		t_flag;	// <ttl> define time to live (TODO)
}				t_ping_flags;


typedef struct	s_ping
{
	char				*destination;
	char				*ip;
	int					socket;
	int					ttl;
	int					interval;
	int					timeout;
	bool				is_running;
	t_ping_flags		flags;
}						t_ping;

extern t_ping	g_ping;

void	sendPing();

int		parseInput(int argc, char **argv);
void	printParams();
void	initParams();
int		dnsLookup();
int		reverseDnsLookup();
int		cleanup();
int		checkRoot();
void	intHandler();

#endif