/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:32:35 by mbico             #+#    #+#             */
/*   Updated: 2024/08/20 16:45:23 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	someone_died(t_philo *philo, unsigned int s_time)
{
	pthread_mutex_lock(&philo->status->dmutex);
	if (philo->status->died)
	{
		pthread_mutex_unlock(&philo->status->dmutex);
		return (TRUE);
	}
	else if (philo->hp <= 0)
	{
		philo->status->died = TRUE;
		mutex_printer("died", philo, s_time);
		pthread_mutex_unlock(&philo->status->dmutex);
		return (TRUE);
	}
	else if (all_meal_clear(philo))
	{
		philo->status->died = TRUE;
		pthread_mutex_unlock(&philo->status->dmutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->status->dmutex);
	return (FALSE);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				nb_meal;

	philo = (t_philo *)arg;
	nb_meal = philo->data.nb_meal;
	if (philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		if (take_fork(philo, philo->data.time))
		{
			if (eating(philo, philo->data.time, &nb_meal)
				|| sleeping(philo, philo->data.time)
				|| thinking(philo, philo->data.time))
				break ;
		}
		else if (waiting(philo, philo->data.time))
			break ;
	}
	return (NULL);
}

void	philo_thread_join(t_philo *philo, int nb_philo,
	t_fork *fork, t_status *status)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i ++;
	}
	free(philo);
	free(fork);
	free(status->mealcount);
}
