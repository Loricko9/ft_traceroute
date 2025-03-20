/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:53:14 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/19 12:53:14 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

bool	ft_strcmp(char *src, char *dest)
{
	int i;

	i = 0;
	while (dest[i] && src[i])
	{
		if (src[i] != dest[i])
			return (false);
		i++;
	}
	if (!src[i])
		return (false);
	return (true);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * sign);
}

bool	ft_is_digit(char *str)
{
	bool	check;
	int		i;

	i = -1;
	check = false;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			check = true;
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9'))
			return (false);
	}
	if (check)
		return (true);
	else
		return (false);
}

void	get_size(char **av, int ac, t_info *info)
{
	int	i;
	int	res;

	i = 0;
	while (++i < ac)
	{
		//printf("s : %s", av[i]);
		if (av[i][0] != '-')
		{
			res = ft_atoi(av[i]);
			if (res <= 0)
			{
				printf("Cannot handle \"packetlen\" cmdline arg `%s'\n", av[i]);
				exit(2);
			}
			else if (res < 28)
				info->send_size = 28;
			else
				info->send_size = res;
			return ;
		}
		if (av[i][0] == '-' && av[i][1] != '-' && !av[i][2])
			i++;
	}
}

char	*get_host_size(char **av, int ac, t_info *info)
{
	char	*res_host;
	int		i;

	i = 0;
	res_host = NULL;
	while (++i < ac)
	{
		if (av[i][0] != '-')
		{
			res_host = av[i];
			break;
		}
		if (av[i][0] == '-' && av[i][1] != '-' && !av[i][2])
			i++;
	}
	if (i == ac)
	{
		printf("Specify \"host\" missing argument.");
		exit(2);
	}
	get_size(av + i, ac - i, info);
	return (res_host);
}
