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
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>

# define TIMEOUT 1

typedef struct s_info
{
	int		dest_port;
	int		max_ttl;
	int		first_ttl;
	int		send_size;
	bool	print_host;
}	t_info;

typedef struct s_pkg_res
{
	struct icmp	*icmp;
	struct ip	*ip;
	double		time;
	int			pkg_nb;
}	t_pkg_res;

/*check_flags.c*/
void	print_help(void);
bool	check_flags(int ac, char **av, t_info *info);

/*socket.c*/
void	init_socket(int (*sock)[2]);
void	change_ttl(int *sock, int ttl);
void	ft_free(int *sock, char *str);

/*package.c*/
bool	convert_ipname(struct sockaddr_in *ip_addr, char *address);
bool	check_ip(struct sockaddr_in *ip_addr, char *address, t_info *info);
bool	check_pkg(t_pkg_res *pkg_res, bool print);
void	create_send_pkg(char *str, int seq, size_t size);

/*get_host.c*/
char	*get_host_size(char **av, int ac, t_info *info);

/*print.c*/
void	print_start(struct sockaddr_in *ip_dest, char *address, t_info *info);
void	print_help(void);
void	print_err_flag(char *err, int cases, int argc);
void	print_err_option(char *flag, char *err, int argc);
void	print_err_resp(int pkg_nb);

/*utils.c*/
bool	ft_strcmp(char *src, char *dest);
int		ft_atoi(const char *nptr);
bool	ft_is_digit(char *str);
void	*ft_memset(void *prt, int nb, size_t len);
void	*ft_memcpy(void *dest, void *src, size_t len);

/*utils2.c*/
double	ft_time(bool cases);
void	init_info(t_info *info);

#endif