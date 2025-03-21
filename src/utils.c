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

void	*ft_memset(void *ptr, int nb, size_t len)
{
	size_t	i;
	
	if (!ptr)
		return (NULL);
	i = 0;
	while(i < len)
	{
		((unsigned char *)ptr)[i] = nb;
		i++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dest, void *src, size_t len)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
