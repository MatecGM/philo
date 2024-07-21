/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:00:03 by mbico             #+#    #+#             */
/*   Updated: 2024/07/21 23:04:04 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	arg_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("arg error : ./philo [nb_philo] [time_die] [time_eat] [time_sleep] optional : [nb_meal]\n");
		return (TRUE);
	}
	return (FALSE);
}

pthread_mutex_t	*init_fork(int nb_philo)
{
	pthread_mutex_t	*forks;
	int				i; 

	forks = ft_calloc(nb_philo + 1, sizeof(pthread_mutex_t));
	while (i < nb)
	{
		forks[i] = pthread_mutex_init(&(forks[i]), NULL);
		i ++;
	}
	return (forks);
}

void	create_philo(char **argv, t_data data)
{
	int		nb;
	int		i;
	t_philo	*philo;

	nb = ft_atoi(argv[1]);
	i = 0;
	philo = ft_calloc(nb + 1, sizeof(t_philo)); 
	while (i < nb)
	{
		
	}
}

t_data	init_data(char **argv)
{
	t_data	data;

	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	printf("avant thread\n");
	// if (arg_error(argc, argv))
	// 	return (1);
	data = init_data(argv);
	printf("apres thread\n");
	return (0);
}

