/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:15:38 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/17 17:15:38 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

bool	wait_response(int *sock, double res_time, int pkg_nb)
{
	char				buff_recv[516];
	struct icmp			*icmp_res;
	struct ip			*ip_res;
	struct sockaddr_in	recv_ip;
	socklen_t			len;

	len = sizeof(recv_ip);
	ft_memset(buff_recv, 0, 516);
	if (recvfrom(sock[1], buff_recv, sizeof(buff_recv), 0,
		(struct sockaddr *)&recv_ip, &len) <= 0)
		return (print_err_resp(pkg_nb), false);
	res_time = ft_time(true);
	ip_res = (struct ip *)buff_recv;
	icmp_res = (struct icmp *)(buff_recv + (ip_res->ip_hl << 2));
	if (check_pkg(ip_res, icmp_res, pkg_nb, res_time))
		return (true);
	return (false);
}

bool	loop_traceroute(int *sock, struct sockaddr_in *ip_dest, t_info *info)
{
	char		*buff_send;
	int			ttl;
	int			packet_nb;
	bool		stop;

	ttl = info->first_ttl - 1;
	stop = false;
	buff_send = malloc(info->send_size);
	while (++ttl <= info->max_ttl && !stop)
	{
		packet_nb = 0;
		change_ttl(sock, ttl);
		while (++packet_nb <= 3)
		{
			ip_dest->sin_port = htons(info->dest_port + (packet_nb - 1));
			create_send_pkg(buff_send, ttl, info->send_size);
			ft_time(false);
			if (sendto(sock[0], buff_send, (size_t)info->send_size, 0,
				(struct sockaddr *)ip_dest, sizeof(*ip_dest)) <= 0)
				return (perror("sendto"), ft_free(sock, buff_send), true);
			if (wait_response(sock, 0.0, packet_nb))
				stop = true;
		}
	}
	return (ft_free(sock, buff_send), false);
}

int	main(int ac, char **av)
{
	struct sockaddr_in	ip_dest;
	t_info				info;
	int					sock[2];
	char				*host;

	info.dest_port = 33434;
	info.max_ttl = 30;
	info.send_size = 52;
	info.first_ttl = 1;
	if (ac < 2)
		print_help();
	check_flags(ac, av, &info);
	if (info.first_ttl > info.max_ttl)
		return(printf("first hop out of range\n"), 2);
	host = get_host_size(av, ac, &info);
	printf("host : %s\n", host);
	printf("port : %d | ttl : %d | 1st ttl : %d | size : %d\n", info.dest_port, info.max_ttl, info.first_ttl, info.send_size);
	init_socket(&sock);
	if (check_ip(&ip_dest, host, &info))
		return (ft_free(sock, NULL), 1);
	print_start(&ip_dest, host, &info);
	loop_traceroute(sock, &ip_dest, &info);
	return (0);
}
