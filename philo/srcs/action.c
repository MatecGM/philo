/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:55:18 by mbico             #+#    #+#             */
/*   Updated: 2024/09/29 02:34:36 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	eating(t_philo *philo, unsigned int s_time, int *nb_meal)
{
	unsigned int	end_loop;
	int				time_start;
	int				time_last;

	end_loop = time_now() + philo->data.time_eat;
	philo->hp = philo->data.time_die * 10;
	*nb_meal -= 1;
	mutex_printer("is eating", philo, s_time);
	time_last = time_now();
	while (end_loop > time_now())
	{
		time_start = time_now();
		usleep(100);
		philo->hp -= (time_start - time_last) * 10;
		if (someone_died(philo, s_time))
			return (TRUE);
		time_last = time_start;
	}
	mutex_set_int(&philo->left->fork, -1, &philo->left->mtx_fork);
	mutex_set_int(&philo->right->fork, -1, &philo->right->mtx_fork);
	if (*nb_meal == 0)
		mutex_set_int(&philo->status->mealcount[philo->id],
			TRUE, &philo->status->mmutex);
	return (FALSE);
}

t_bool	thinking(t_philo *philo, unsigned int s_time)
{
	int				time_start;
	int				time_last;

	mutex_printer("is thinking", philo, s_time);
	time_last = time_now();
	while (!take_fork(philo, s_time))
	{
		time_start = time_now();
		usleep(1000);
		philo->hp -= (time_start - time_last) * 10;
		if (someone_died(philo, s_time))
			return (TRUE);
		time_last = time_start;
	}
	return (FALSE);
}

t_bool	waiting(t_philo *philo, unsigned int s_time)
{
	int				time_start;
	int				time_last;

	if (someone_died(philo, s_time))
		return (TRUE);
	time_last = time_now();
	while (!take_fork(philo, s_time))
	{
		time_start = time_now();
		usleep(100);
		philo->hp -= (time_start - time_last) * 10;
		if (someone_died(philo, s_time))
			return (TRUE);
		time_last = time_start;
	}
	return (FALSE);
}

t_bool	sleeping(t_philo *philo, unsigned int s_time)
{
	unsigned int	end_loop;
	int				time_start;
	int				time_last;

	end_loop = time_now() + philo->data.time_sleep;
	mutex_printer("is sleeping", philo, s_time);
	time_last = time_now();
	while (end_loop > time_now())
	{
		time_start = time_now();
		usleep(100);
		philo->hp -= (time_start - time_last) * 10;
		if (someone_died(philo, s_time))
			return (TRUE);
		time_last = time_start;
	}
	return (FALSE);
}

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
	if (philo->data.alone)
	{
		usleep(philo->data.time_die * 1000);
		philo->hp = 0;
		return (0);
	}
	return (mutex_checker(&philo->left->fork,
			&philo->left->mtx_fork) == philo->id
		&& mutex_checker(&philo->right->fork,
			&philo->right->mtx_fork) == philo->id);
}
