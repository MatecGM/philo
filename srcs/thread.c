/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:32:35 by mbico             #+#    #+#             */
/*   Updated: 2024/07/29 02:45:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



t_bool	take_fork(t_philo *philo, unsigned int s_time)
{
	if (mutex_checker(&philo->left->fork, &philo->left->mtx_fork) == -1)
	{
		mutex_printer("has taken a fork", philo, s_time);
		mutex_set_int(&philo->left->fork, philo->id, &philo->left->mtx_fork);
	}
	if (mutex_checker(&philo->right->fork, &philo->right->mtx_fork) == -1)
	{
		mutex_printer("has taken a fork", philo, s_time);
		mutex_set_int(&philo->right->fork, philo->id, &philo->right->mtx_fork);
	}
	return (philo->left->fork == philo->id && philo->right->fork == philo->id);
}

t_bool	someone_died(t_philo *philo, unsigned int s_time, int nb_meal)
{
	pthread_mutex_lock(&philo->status->dmutex);
	if (philo->status->died)
	{
		pthread_mutex_unlock(&philo->status->dmutex);
		return(TRUE);
	}
	else if (philo->hp <= 0)
	{
		philo->status->died = TRUE;
		mutex_printer("died", philo, s_time);
		pthread_mutex_unlock(&philo->status->dmutex);
		return (TRUE);
	}
	else if (nb_meal == 0)
	{
		philo->status->died = TRUE;
		pthread_mutex_unlock(&philo->status->dmutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->status->dmutex);
	return (FALSE);
}

t_bool	eat(t_philo *philo, unsigned int s_time, int *nb_meal)
{
	int	ml_sec;
	
	ml_sec = philo->data.time_eat;
	philo->hp = philo->data.time_die;
	*nb_meal -= 1;
	mutex_printer("is eating", philo, s_time);
	while (ml_sec > 0)
	{
		usleep(10000);
		ml_sec -= 10;
		philo->hp -= 10;
		if (someone_died(philo, s_time, *nb_meal))
			return (TRUE);
	}
	mutex_set_int(&philo->left->fork, -1, &philo->left->mtx_fork);
	mutex_set_int(&philo->right->fork, -1, &philo->right->mtx_fork);
	return (FALSE);
}

t_bool	think(t_philo *philo, unsigned int s_time, int nb_meal)
{
	mutex_printer("is thinking", philo, s_time);
	while(!take_fork(philo, s_time))
	{
		usleep(2000);
		philo->hp -= 2;
		if (someone_died(philo, s_time, nb_meal))
			return (TRUE);
	}
	return (FALSE);
}

t_bool	waiting(t_philo *philo, unsigned int s_time, int nb_meal)
{
	while(!take_fork(philo, s_time))
	{
		usleep(2000);
		philo->hp -= 2;
		if (someone_died(philo, s_time, nb_meal))
			return (TRUE);
	}
	return (FALSE);
}

t_bool	sleep_time(t_philo *philo, unsigned int s_time, int nb_meal)
{
	int	ml_sec;
	
	ml_sec = philo->data.time_sleep;
	mutex_printer("is sleeping", philo, s_time);
	while (ml_sec > 0)
	{
		usleep(10000);
		ml_sec -= 10;
		philo->hp -= 10;
		if (someone_died(philo, s_time, nb_meal))
			return (TRUE);
	}
	return (FALSE);
}


unsigned int	time_now(void)
{
	struct timeval	time_now;
	unsigned int	time_convert_ml;

	gettimeofday(&time_now, NULL);
	time_convert_ml = time_now.tv_sec * 1000 + time_now.tv_usec	/ 1000;
	return (time_convert_ml);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	unsigned int 	s_time;
	int				nb_meal;
	
	usleep(10000);
	philo = (t_philo *)arg;
	nb_meal = philo->data.nb_meal;
	if (philo->id % 2 == 1)
		usleep(500);
	s_time = time_now();
	while (1)
	{
		if (take_fork(philo, s_time))
		{
			if (eat(philo, s_time, &nb_meal) || sleep_time(philo, s_time, nb_meal) || think(philo, s_time, nb_meal))
				break;
		}
		else if (waiting(philo, s_time, nb_meal))
			break;
		
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