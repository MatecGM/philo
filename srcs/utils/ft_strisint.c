/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:44:22 by mbico             #+#    #+#             */
/*   Updated: 2024/07/30 17:16:54 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	ft_atol(const char *nptr)
{
	long int	nbr;
	long int	sign;

	nbr = 0;
	sign = 1;
	while ((*nptr && *nptr == ' ') || (*nptr && *nptr >= 9 && *nptr <= 13))
		nptr ++;
	if (*nptr && (*nptr == '+' || *nptr == '-'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr ++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		nptr ++;
	}
	nbr *= sign;
	return (nbr);
}

int	ft_strnblen(char *str)
{
	int	len;

	len = 0;
	if (*str && (*str == '-' || *str == '+'))
		str ++;
	while (*str && *str == '0')
		str ++;
	while (*str)
	{
		str ++;
		len ++;
	}
	return (len);
}

int	ft_strisint(char *str)
{
	int			len;
	long int	nb;
	char		*tmp;

	tmp = str;
	if (*tmp == ' ' || *tmp == '+' || *tmp == '-')
		tmp ++;
	while (*tmp)
	{
		if (*tmp < '0' || *tmp > '9')
			return (0);
		tmp ++;
	}
	len = ft_strnblen(str);
	nb = ft_atol(str);
	if (len <= 11 && nb <= 2147483647 && nb >= -2147483648)
		return (1);
	return (0);
}
