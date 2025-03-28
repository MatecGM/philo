/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:06:44 by mbico             #+#    #+#             */
/*   Updated: 2024/08/20 16:19:22 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_meal_checker(t_status *status, int nb_philo)
{
	status->mealcount = ft_calloc(nb_philo + 1, sizeof(t_bool));
	if (!status->mealcount)
		return (TRUE);
	status->mealcount[nb_philo] = ERROR;
	if (pthread_mutex_init(&status->mmutex, NULL))
		return (TRUE);
	return (FALSE);
}

t_bool	all_meal_clear(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->status->mmutex);
	while (philo->status->mealcount[i] != ERROR)
	{
		if (!philo->status->mealcount[i])
		{
			pthread_mutex_unlock(&philo->status->mmutex);
			return (FALSE);
		}
		i ++;
	}
	pthread_mutex_unlock(&philo->status->mmutex);
	return (TRUE);
}
