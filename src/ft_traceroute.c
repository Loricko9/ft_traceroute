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
	// int		i;
	// bool	flag_v;

	if (ac < 2)
		print_help();
	check_flags(ac, av);
	// i = 0;
	// while (++i < ac)
	// {
	// 	if (av[i][0] != '-')
	// 		start_ping(av[i], init_socket(), flag_v);
	// }
	return (0);
}