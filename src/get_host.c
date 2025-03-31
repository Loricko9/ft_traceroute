/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_host.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:23:28 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/20 12:23:28 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	check_arg(char *arg, int argc)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if ((arg[i] < '0' || arg[i] > '9') && arg[i] != ' ')
		{
			printf("Cannot handle \"packetlen\" cmdline arg `%s'", arg);
			printf(" on position 2 (argc %d)", argc);
			exit(2);
		}
	}
}

void	err_size_invalid(char *str)
{
	printf("Cannot handle \"packetlen\" cmdline arg `%s'\n", str);
	exit(2);
}

void	err_size_big(int nb)
{
	printf("too big packetlen %d specified\n", nb);
	exit(2);
}

void	get_size(char **av, int ac, t_info *info)
{
	int	i;
	int	res;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
		{
			check_arg(av[i], i);
			res = ft_atoi(av[i]);
			if (res <= 0)
				err_size_invalid(av[i]);
			else if (res < 28)
				info->send_size = 20;
			else if (res > 65000)
				err_size_big(res);
			else
				info->send_size = res - 8;
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
		if (av[i][0] != '-' || (av[i][0] == '-' && !av[i][1]))
		{
			res_host = av[i];
			break ;
		}
		if (av[i][0] == '-' && ((av[i][1] != '-' && !av[i][2]
			&& av[i][1] != 'n' )|| (av[i][1] == 'n' && av[i][2])))
			i++;
	}
	if (i == ac)
	{
		printf("Specify \"host\" missing argument.\n");
		exit(2);
	}
	get_size(av + i, ac - i, info);
	return (res_host);
}
