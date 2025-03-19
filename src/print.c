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
	printf("traceroute to %s (%s), %d hops max, %d byte packets",
		address, host, info->max_ttl, info->send_size);
}

void	print_help(void)
{
	printf("Usage:\n");
	printf("  traceroute host\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	exit(0);
}

void	print_err_flag(char *err, int cases, int argc)
{
	if (cases == 0)
		printf("Extra arg `%s' (argc %d)\n", err, argc);
	else
		printf("Bad option `%s' (argc %d)\n", err, argc);
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
