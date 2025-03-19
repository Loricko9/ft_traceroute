/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:05:36 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/18 18:05:36 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

bool	check_pkg(struct ip *ip_res, struct icmp *icmp_res, int ttl)
{
	char	host[INET_ADDRSTRLEN];

	if (!ip_res || !icmp_res)
		return (true);
	if (icmp_res->icmp_type == ICMP_DEST_UNREACH)
		return (false);
	if (inet_ntop(AF_INET, &(ip_res->ip_src), host, INET_ADDRSTRLEN) == NULL)
		fprintf(stderr, "error inet_ntop\n");
	printf(" %d  \n", ttl);
	return (true);
}

bool	convert_hostname(struct sockaddr_in *ip_addr, char *address)
{
	struct addrinfo	hint;
	struct addrinfo	*res;
	int				ret;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_DGRAM;
	ret = getaddrinfo(address, NULL, &hint, &res);
	if (ret != 0)
	{
		printf("%s: Name or service not known\n", address);
		printf("Cannot handle \"host\" cmdline arg `%s'", address);
		return (true);
	}
	memcpy(ip_addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return (false);
}

bool	check_ip(struct sockaddr_in *ip_addr, char *address, t_info *info)
{
	memset(ip_addr, 0, sizeof(*ip_addr));
	ip_addr->sin_family = AF_INET;
	ip_addr->sin_port = htons(info->dest_port);
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
		if (convert_hostname(ip_addr, address))
			return (true);
	return (false);
}
