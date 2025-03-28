/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:48:07 by mbico             #+#    #+#             */
/*   Updated: 2024/08/20 16:39:06 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv, int argc)
{
	t_data	data;

	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	data.alone = ft_atoi(argv[1]) == 1;
	data.time = time_now();
	if (argc == 6)
		data.nb_meal = ft_atoi(argv[5]);
	else
		data.nb_meal = -1;
	return (data);
}

t_bool	init_status(t_status *status, char *nb)
{
	status->died = FALSE;
	if (pthread_mutex_init(&status->dmutex, NULL)
		|| pthread_mutex_init(&status->print, NULL)
		|| init_meal_checker(status, ft_atoi(nb)))
		return (TRUE);
	return (FALSE);
}

t_fork	*init_fork(int nb_philo)
{
	t_fork	*forks;
	int		i;

	forks = ft_calloc(nb_philo + 1, sizeof(t_fork));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i].mtx_fork, NULL))
			return (NULL);
		forks[i].fork = -1;
		i ++;
	}
	return (forks);
}

void	give_fork(t_philo *philo, t_fork *forks, int i, int nb_philo)
{
	philo->left = &forks[i];
	philo->right = &forks[(i + 1) % nb_philo];
}

t_philo	*init_philo(t_data data, t_fork *forks, t_status *status, int nb_philo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = ft_calloc(nb_philo + 1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (i < nb_philo)
	{
		philo[i].hp = data.time_die * 10;
		philo[i].id = i;
		philo[i].data = data;
		give_fork(&philo[i], forks, i, nb_philo);
		philo[i].status = status;
		if (pthread_create(&philo[i].thread, NULL, routine, &(philo[i])))
			return (NULL);
		i ++;
	}
	return (philo);
}
