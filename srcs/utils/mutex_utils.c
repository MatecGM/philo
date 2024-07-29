/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:41:09 by mbico             #+#    #+#             */
/*   Updated: 2024/07/29 01:58:28 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_checker(int *nb, pthread_mutex_t *mutex)
{
	t_bool	value;

	pthread_mutex_lock(mutex);
	value = *nb;
	pthread_mutex_unlock(mutex);
	return (value);
}
void	mutex_set_int(int *var, int new, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = new;
	pthread_mutex_unlock(mutex);
}

void	mutex_printer(char *msg, t_philo *philo, unsigned int start_time)
{
	unsigned int rel_time;

	rel_time = time_now() - start_time;
	pthread_mutex_lock(&philo->status->print);
	printf("%u %d %s\n", rel_time, philo->id, msg);
	pthread_mutex_unlock(&philo->status->print);
}
