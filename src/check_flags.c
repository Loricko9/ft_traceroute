/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:25:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/28 09:47:59 by lle-saul         ###   ########.fr       */
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
	else if (str)
		print_err_option("-m", str_next, argc);
	else
		print_err_option("--max-hops", str_next, argc);
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
	else if (str)
		print_err_option("-p", str_next, argc);
	else
		print_err_option("--port", str_next, argc);
	info->dest_port = res;
}

void	get_first_ttl(char *str, char *str_next, int argc, t_info *info)
{
	int	res;

	if (str && str[2] && ft_is_digit(str + 2))
		res = ft_atoi(str + 2);
	else if (str_next && ft_is_digit(str_next))
		res = ft_atoi(str_next);
	else if (str && str[2])
		print_err_option("-f", str + 2, argc);
	else if (str)
		print_err_option("-f", str_next, argc);
	else
		print_err_option("--first", str_next, argc);
	if (res <= 0)
	{
		printf("first hop out of range\n");
		exit(2);
	}
	info->first_ttl = res;
}

void	check_flags_letter(char *str, char *str_next, int argc, t_info *info)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'm')
			get_ttl(str, str_next, argc, info);
		else if (str[i] == 'p')
			get_port(str, str_next, argc, info);
		else if (str[i] == 'f')
			get_first_ttl(str, str_next, argc, info);
		else if (str[i] == 'r')
			info->print_host = false;
		else
			print_err_flag(str + i, 2, argc);
	}
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
			else if (ft_strcmp(av[i] + 2, "first="))
				get_first_ttl(NULL, av[i] + 8, i, info);
			else
				print_err_flag(av[i], 1, i);
		}
	}
	return (false);
}
