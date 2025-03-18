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

bool	convert_hostname(struct sockaddr_in *ip_addr, char *address, int pos)
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
		printf(" on position 1 (argc %d)\n", pos);
		return (true);
	}
	memcpy(ip_addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return (false);
}

bool	check_ip(struct sockaddr_in *ip_addr, char *address, int pos)
{
	memset(ip_addr, 0, sizeof(*ip_addr));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
		if (convert_hostname(ip_addr, address, pos))
			return (true);
	return (false);
}
