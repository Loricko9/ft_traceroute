/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:25:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/18 10:38:41 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help(void)
{
	printf("Usage:\n");
	printf("  traceroute host\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	exit(0);
}

void	print_err_flag(char *err, int cases, int argc)
{
	if (cases == 0)
		printf("Extra arg `%s' (argc %d)\n", err, argc);
	else
		printf("Bad option `%s' (argc %d)\n", err, argc);
	exit(2);
}

void	check_flags_letter(char *str, int argc)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		// if (str[i] == '?')
		// 	print_help();
		// else if (str[i] == 'v')
		// 	*res = true;
		if (str[i] == ' ')
			print_err_flag(str + i + 1, 0, argc);
		else
			print_err_flag(str, 1, argc);
	}
}

void	check_flags2(char *arg, int i)
{
	if (strcmp(arg + 2, "help") == 0)
		print_help();
	else
		print_err_flag(arg, 1, i);
}

bool	check_flags(int ac, char **av)
{
	int		i;
	int		j;
	// bool	res;

	i = 0;
	j = 0;
	// res = false;
	while (++i < ac)
	{
		if (j > 2)
			print_err_flag(av[i - 1], 0, i - 1);
		else if (av[i][0] && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
			check_flags_letter(av[i], i);
		else if (av[i][0] && av[i][1] && av[i][0] == '-' && av[i][1] == '-')
			check_flags2(av[i], i);
		else
			j++;
	}
	if (j > 2)
		print_err_flag(av[i - 1], 0, i - 1);
	return (false);
}
