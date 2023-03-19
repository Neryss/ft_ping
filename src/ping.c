#include "../include/ping.h"

int	dnsLookup()
{
	struct addrinfo	hints;
	struct addrinfo	*res = NULL;
	int				error = 0;

	ft_memset(&hints, '\0', sizeof(hints));
	error = getaddrinfo(g_params.destination, NULL, &hints, &res);
	if (error)
	{
		printf("Error in addrinfo\n");
		return (1);
	}
	char ip[50] = "";
	inet_ntop(AF_INET, &res->ai_addr->sa_data[2], ip, sizeof(ip));
	printf("ip: %s\n", ip);
	return (0);
}