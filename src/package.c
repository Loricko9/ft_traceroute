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

#include "ft_traceroute.h"

void	create_send_pkg(char *str, int seq, size_t size)
{
	struct timeval	tv;
	int				pid;

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

void	print_pkg(char *ip, struct sockaddr_in recv_addr, bool print,
					t_pkg_res *pkg_res)
{
	static char			last_ip[INET_ADDRSTRLEN] = {0};
	char				hostname[NI_MAXHOST];

	if (getnameinfo((struct sockaddr *)&recv_addr, sizeof(recv_addr), hostname,
			NI_MAXHOST, NULL, 0, NI_NAMEREQD) == 0 && (pkg_res->pkg_nb == 1
			|| !ft_strcmp(ip, last_ip)) && print)
		printf(" %s (%s)  %.3f ms", hostname, ip, pkg_res->time);
	else if (pkg_res->pkg_nb == 1 || !ft_strcmp(ip, last_ip))
		printf(" %s  %.3f ms", ip, pkg_res->time);
	else
		printf("  %.3f ms", pkg_res->time);
	if (pkg_res->pkg_nb == 3)
		printf("\n");
	ft_memcpy(last_ip, ip, INET_ADDRSTRLEN);
}

bool	check_pkg(t_pkg_res *pkg_res, bool print)
{
	char				ip[INET_ADDRSTRLEN];
	struct sockaddr_in	recv_addr;

	if (!pkg_res->ip || !pkg_res->icmp)
		return (false);
	if (inet_ntop(AF_INET, &(pkg_res->ip->ip_src), ip, INET_ADDRSTRLEN)
		== NULL)
		fprintf(stderr, "error inet_ntop\n");
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_addr = pkg_res->ip->ip_src;
	print_pkg(ip, recv_addr, print, pkg_res);
	if (pkg_res->icmp->icmp_type == ICMP_DEST_UNREACH)
		return (true);
	return (false);
}

bool	convert_ipname(struct sockaddr_in *ip_addr, char *address)
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
		printf("Cannot handle \"ip\" cmdline arg `%s'", address);
		return (true);
	}
	ft_memset(ip_addr, 0, sizeof(struct sockaddr_in));
	ft_memcpy(ip_addr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	return (false);
}

bool	check_ip(struct sockaddr_in *ip_addr, char *address, t_info *info)
{
	ft_memset(ip_addr, 0, sizeof(struct sockaddr_in));
	ip_addr->sin_family = AF_INET;
	if (inet_pton(AF_INET, address, &ip_addr->sin_addr) <= 0)
		if (convert_ipname(ip_addr, address))
			return (true);
	ip_addr->sin_port = htons(info->dest_port);
	return (false);
}
