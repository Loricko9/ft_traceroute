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
# include <unistd.h>
# include <netdb.h>
# include <sys/socket.h>
 #include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>

/*check_flags.c*/
void	print_help(void);
bool	check_flags(int ac, char **av);

/*socket.c*/
void	init_socket(int (*sock)[2]);
void	change_ttl(int *sock, int ttl);
void	ft_free(int *sock);

/*package.c*/
bool	convert_hostname(struct sockaddr_in *ip_addr, char *address, int pos);
bool	check_ip(struct sockaddr_in *ip_addr, char *address, int pos);

#endif