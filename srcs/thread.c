/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:32:35 by mbico             #+#    #+#             */
/*   Updated: 2024/07/25 19:14:13 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_time(t_philo *philo)
{
	int	ml_sec;
	
	mutex_set_int(&philo->left->fork, TRUE, &philo->left->mtx_fork);
	mutex_set_int(&philo->right->fork, TRUE, &philo->right->mtx_fork);
	mutex_printer("eat !", philo);
	ml_sec = 0;
	while (ml_sec < philo->data.time_eat)
	{
		usleep(1000);
		ml_sec ++;
	}
	mutex_set_int(&philo->left->fork, FALSE, &philo->left->mtx_fork);
	mutex_set_int(&philo->right->fork, FALSE, &philo->right->mtx_fork);
	usleep(100000);
}



void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	mutex_printer(" is init", philo);
	
	if (philo->id % 2 == 1)
		usleep(10000);
	while (!mutex_checker(&philo->status->died, &philo->status->dmutex))
	{
		if (mutex_checker(&philo->left->fork, &philo->left->mtx_fork) == FALSE &&
			mutex_checker(&philo->right->fork, &philo->right->mtx_fork) == FALSE)
			eat_time(philo);
		else
		{
			mutex_printer("no eating !", philo);
			while(mutex_checker(&philo->left->fork, &philo->left->mtx_fork) == TRUE &&
				mutex_checker(&philo->right->fork, &philo->right->mtx_fork) == TRUE)
			{
				usleep(10000);
			}
		}
	}
	pthread_exit(NULL);
}

void	philo_thread_join(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i ++;
	}
	free(philo);
}