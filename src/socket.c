/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:51:14 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/18 17:51:14 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*sock[0] = sock_UDP | sock[1] = sock_ICMP*/
void	init_socket(int (*sock)[2])
{
	struct timeval	timeout;

	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	(*sock)[0] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	(*sock)[1] = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if ((*sock)[0] < 0 || (*sock)[1] < 0)
	{
		fprintf(stderr, "Socket creation error");
		exit(1);
	}
	if (setsockopt((*sock)[1], SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)))
	{
		fprintf(stderr, "Setsocket option error");
		ft_free(*sock, NULL);
		exit(1);
	}
}

void	change_ttl(int *sock, int ttl)
{
	if (setsockopt(sock[0], IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
	{
		fprintf(stderr, "Setsocket option error");
		ft_free(sock, NULL);
		exit(1);
	}
}

void	ft_free(int *sock, char *str)
{
	close(sock[0]);
	close(sock[1]);
	if (str)
		free(str);
}
