/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:01:26 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/24 12:01:26 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*false => memorise time start | true => get time*/
double	ft_time(bool cases)
{
	static struct timeval	start;
	struct timeval			end;
	double					res;

	if (!cases)
		gettimeofday(&start, NULL);
	else
	{
		gettimeofday(&end, NULL);
		res = (end.tv_usec - start.tv_usec) / 1000.0
			+ (end.tv_sec - start.tv_sec) * 1000.0;
	}
	return (res);
}

void	init_info(t_info *info)
{
	info->dest_port = 33434;
	info->max_ttl = 30;
	info->send_size = 52;
	info->first_ttl = 1;
	info->print_host = true;
}
