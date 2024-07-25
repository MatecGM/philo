/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:41:09 by mbico             #+#    #+#             */
/*   Updated: 2024/07/25 17:58:58 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	mutex_checker(t_bool *bool, pthread_mutex_t *mutex)
{
	t_bool	value;

	pthread_mutex_lock(mutex);
	value = *bool;
	pthread_mutex_unlock(mutex);
	return (value);
}
void	mutex_set_int(int *var, int new, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = new;
	pthread_mutex_unlock(mutex);
}

void	mutex_printer(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->status->print);
	printf("Philo %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->status->print);
}
