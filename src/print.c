/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:12:09 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/19 12:12:09 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_start(struct sockaddr_in *ip_dest, char *address, t_info *info)
{
	char	host[INET_ADDRSTRLEN];

	if (inet_ntop(AF_INET, &(ip_dest->sin_addr), host, INET_ADDRSTRLEN) == NULL)
		fprintf(stderr, "error inet_ntop\n");
	if (info->send_size + 8 <= 28)
		printf("traceroute to %s (%s), %d hops max, 28 byte packets\n",
			address, host, info->max_ttl);
	else
		printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
			address, host, info->max_ttl, info->send_size + 8);
}

void	print_help(void)
{
	printf("Usage:\n");
	printf("  traceroute [ -m max_ttl ] [ -p port ] host [ packetlen ]\n\n");
	printf("Options:\n");
	printf("  -f first_ttl  --first=first_ttl\n");
	printf("\t\t\t\tStart from the first_ttl hop (instead from 1)\n");
	printf("  -m max_ttl  --max-hops=max_ttl\n");
	printf("\t\t\t\tSet the max number of hops (max TTL to be\n");
	printf("\t\t\t\treached). Default is 30\")\n");
	printf("  -n\t\t\t\tDo not resolve IP addresses to their domain names\n");
	printf("  -p port  --port=port          Set the destination port to use. ");
	printf("It is either\n\t\t\t\tinitial udp port value for \"default\" ");
	printf("method\n\t\t\t\t(incremented by each probe, default is 33434)\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	printf("      packetlen     The full packet length (default is the length");
	printf(" of an IP\n                    header plus 40). Can be ignored");
	printf(" or increased to a minimal\n                    allowed value");
	exit(0);
}

void	print_err_flag(char *err, int cases, int argc)
{
	if (cases == 0)
		printf("Extra arg `%s' (argc %d)\n", err, argc);
	else if (cases == 1)
		printf("Bad option `%s' (argc %d)\n", err, argc);
	else
		printf("Bad option `-%c' (argc %d)\n", *err, argc);
	exit(2);
}

void	print_err_option(char *flag, char *err, int argc)
{
	if (!err)
		printf("Cannot handle `%s' option with arg `' (argc %d)\n", flag, argc);
	else
		printf("Cannot handle `%s' option with arg `%s' (argc %d)\n",
			flag, err, argc);
	exit(2);
}

void	print_err_resp(int pkg_nb)
{
	printf(" *");
	if (pkg_nb == 3)
		printf("\n");
}
