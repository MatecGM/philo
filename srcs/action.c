/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:55:18 by mbico             #+#    #+#             */
/*   Updated: 2024/07/30 19:21:52 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	eating(t_philo *philo, unsigned int s_time, int *nb_meal)
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

t_bool	thinking(t_philo *philo, unsigned int s_time, int nb_meal)
{
	mutex_printer("is thinking", philo, s_time);
	while (!take_fork(philo, s_time))
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
	if (someone_died(philo, s_time, nb_meal))
		return (TRUE);
	while (!take_fork(philo, s_time))
	{
		usleep(2000);
		philo->hp -= 2;
		if (someone_died(philo, s_time, nb_meal))
			return (TRUE);
	}
	return (FALSE);
}

t_bool	sleeping(t_philo *philo, unsigned int s_time, int nb_meal)
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
	if (&philo->left->fork == &philo->right->fork)
	{
		usleep(philo->data.time_die * 1000);
		philo->hp = 0;
		return (0);
	}
	return (philo->left->fork == philo->id && philo->right->fork == philo->id);
}
