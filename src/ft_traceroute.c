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

bool	wait_response(int *sock, struct icmp *icmp_res, struct ip *ip_res)
{
	char				buff_recv[516];
	struct sockaddr_in	recv_ip;

	if (recvfrom(sock[1], buff_recv, sizeof(buff_recv), 0,
		(struct sockaddr *)&recv_ip, NULL) <= 0)
		return (perror("recvfrom"), true);
	ip_res = (struct ip *)buff_recv;
	icmp_res = (struct icmp *)(buff_recv + (ip_res->ip_hl << 2));
	(void)icmp_res;
	return (false);
}

bool	loop_traceroute(int *sock, struct sockaddr_in *ip_dest, t_info *info)
{
	struct icmp	icmp_res;
	struct ip	ip_res;
	char		*buff_send;
	int			ttl;

	ttl = 1;
	buff_send = malloc(info->send_size);
	while (ttl <= info->max_ttl)
	{
		create_send_pkg(buff_send, ttl, info->send_size);
		change_ttl(sock, ttl);
		if (sendto(sock[0], buff_send, (size_t)info->send_size, 0,
			(struct sockaddr *)ip_dest, sizeof(*ip_dest)) <= 0)
			return (perror("sendto"), ft_free(sock, buff_send), true);
		wait_response(sock, &icmp_res, &ip_res);
		if (check_pkg(&ip_res, &icmp_res, ttl))
			break;
		ttl++;
	}
	ft_free(sock, buff_send);
	return (false);
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
	if (ac < 2)
		print_help();
	check_flags(ac, av, &info);
	host = get_host_size(av, ac, &info);
	printf("host : %s\n", host);
	printf("port : %d | ttl : %d | size : %d\n", info.dest_port, info.max_ttl, info.send_size);
	init_socket(&sock);
	if (check_ip(&ip_dest, host, &info))
		return (ft_free(sock, NULL), 1);
	print_start(&ip_dest, host, &info);
	loop_traceroute(sock, &ip_dest, &info);
	return (0);
}
