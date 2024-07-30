/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:57:01 by mbico             #+#    #+#             */
/*   Updated: 2024/07/30 19:10:53 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	time_now(void)
{
	struct timeval	time_now;
	unsigned int	time_convert_ml;

	gettimeofday(&time_now, NULL);
	time_convert_ml = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (time_convert_ml);
}
