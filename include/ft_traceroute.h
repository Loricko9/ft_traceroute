/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:16:08 by lle-saul          #+#    #+#             */
/*   Updated: 2025/03/17 17:16:08 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

/*check_flags.c*/
void	print_help(void);
bool	check_flags(int ac, char **av);

#endif