/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:25:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/19 17:09:49 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	get_ttl(char *str, char *str_next, int argc, t_info *info)
{
	int	res;
	
	if (str && str[2] && ft_is_digit(str + 2))
		res = ft_atoi(str + 2);
	else if (str_next && ft_is_digit(str_next))
		res = ft_atoi(str_next);
	else if (str && str[2])
		print_err_option("-m", str + 2, argc);
	else
		print_err_option("-m", str_next, argc);
	if (res <= 0 || res > 255)
	{
		printf("max hops cannot be more than 255\n");
		exit(2);
	}
	info->max_ttl = res;
}

void	get_port(char *str, char *str_next, int argc, t_info *info)
{
	int	res;
	
	if (str && str[2] && ft_is_digit(str + 2))
		res = ft_atoi(str + 2);
	else if (str_next && ft_is_digit(str_next))
		res = ft_atoi(str_next);
	else if (str && str[2])
		print_err_option("-p", str + 2, argc);
	else
		print_err_option("-p", str_next, argc);
	info->dest_port = res;
}

void	check_flags_letter(char *str, char *str_next, int argc, t_info *info)
{
	if (str[1] == 'm')
		get_ttl(str, str_next, argc, info);
	else if (str[1] == 'p')
		get_port(str, str_next, argc, info);
	else
		print_err_flag(str, 1, argc);
}

bool	check_flags(int ac, char **av, t_info *info)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
			check_flags_letter(av[i], av[i + 1], i, info);
		else if (av[i][0] && av[i][1] && av[i][0] == '-' && av[i][1] == '-')
		{
			if (ft_strcmp(av[i] + 2, "help"))
				print_help();
			else if (ft_strcmp(av[i] + 2, "port="))
				get_port(NULL, av[i] + 7, i, info);
			else if (ft_strcmp(av[i] + 2, "max-hops="))
				get_ttl(NULL, av[i] + 11, i, info);
			else
				print_err_flag(av[i], 1, i);
		}
	}
	return (false);
}
