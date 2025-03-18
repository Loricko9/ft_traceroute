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



int	main(int ac, char **av)
{
	struct sockaddr_in	ip_dest;
	int					sock[2];
	int					i;

	if (ac < 2)
		print_help();
	check_flags(ac, av);
	init_socket(&sock);
	i = 1;
	while (i < ac && av[i][0] == '-')
		i++;
	check_ip(&ip_dest, av[i], i);
	return (0);
}
