#include "../include/ping.h"

int	reverseDnsLookup()
{
	//todo
	return (0);
}

int	dnsLookup()
{
	struct addrinfo	hints;
	struct addrinfo	*res = NULL;
	int				error = 0;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_CANONNAME;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	error = getaddrinfo(g_params.destination, NULL, &hints, &res);
	if (error)
	{
		printf("Error in addrinfo\n");
		return (1);
	}
	char ip[50] = "";
	inet_ntop(AF_INET, &res->ai_addr->sa_data[2], ip, sizeof(ip));
	printf("ip: %s\n", ip);

	// Might need to check again
	struct addrinfo	*p = NULL;

	char fqdn[NI_MAXHOST];
	for (p = res; p != NULL; p = p->ai_next)
		if (p->ai_canonname)
		{
			ft_strncpy(fqdn, p->ai_canonname, NI_MAXHOST - 1);
			break;
		}
	printf("fqdn: %s\n", fqdn);
	freeaddrinfo(res);
	return (0);
}