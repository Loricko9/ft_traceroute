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

void	create_send_pkg(char *str, int seq, size_t size)
{
	struct timeval tv;
	int	pid;
	
	if (str == NULL)
		return ;
	ft_memset(str, 0, size);
	pid = getpid();
	ft_memcpy(str, &pid, sizeof(pid));
	ft_memcpy(str + 4, &seq, sizeof(seq));
    gettimeofday(&tv, NULL);
    ft_memcpy(str + 8, &tv, sizeof(tv));
	ft_memset(str + 16, 'A', size - 16);
}

bool	check_pkg(struct ip *ip_res, struct icmp *icmp_res, int pkg_nb, double res_time)
{
	static char	last_host[INET_ADDRSTRLEN] = {0};
	char		host[INET_ADDRSTRLEN];

	if (!ip_res || !icmp_res)
		return (false);
	if (inet_ntop(AF_INET, &(ip_res->ip_src), host, INET_ADDRSTRLEN) == NULL)
		fprintf(stderr, "error inet_ntop\n");
	if (pkg_nb == 1 || !ft_strcmp(host, last_host))
		printf(" %s  %.3f ms", host, res_time);
	else
		printf("  %.3f ms", res_time);
	if (pkg_nb == 3)
		printf("\n");
	ft_memcpy(last_host, host, INET_ADDRSTRLEN);
	if (icmp_res->icmp_type == ICMP_DEST_UNREACH)
		return (true);
	return (false);
}

bool	convert_hostname(struct sockaddr_in *ip_addr, char *address)
{
	struct addrinfo	hint;
	struct addrinfo	*res;
	int				ret;

	ft_memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_DGRAM;
	ret = getaddrinfo(address, NULL, &hint, &res);
	if (ret != 0)
	{
		printf("%s: Name or service not known\n", address);
		printf("Cannot handle \"host\" cmdline arg `%s'", address);
		return (true);
	}
	ft_memset(ip_addr, 0, sizeof(struct sockaddr_in));
	ft_memcpy(ip_addr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	return (false);
}

bool		check_ip(struct sockaddr_in *ip_addr, char *address, t_info *info)
{
	ft_memset(ip_addr, 0, sizeof(struct sockaddr_in));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
		if (convert_hostname(ip_addr, address))
			return (true);
	ip_addr->sin_port = htons(info->dest_port);
	return (false);
}
