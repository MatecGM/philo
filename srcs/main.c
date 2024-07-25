/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:00:03 by mbico             #+#    #+#             */
/*   Updated: 2024/07/23 18:37:43 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

t_bool	arg_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("arg error : ./philo [nb_philo] [time_die] [time_eat] [time_sleep] optional : [nb_meal]\n");
		return (TRUE);
	}
	return (FALSE);
}


int	main(int argc, char **argv)
{
	t_data		data;
	t_status	status[1];
	t_fork		*fork;
	t_philo		*philo;
	int			nb_philo;
	
	printf("avant thread\n");
	// if (arg_error(argc, argv))
	// 	return (1);
	nb_philo = ft_atoi(argv[1]);
	data = init_data(argv);
	fork = init_fork(nb_philo);
	init_status(status);
	philo = init_philo(data, fork, status, nb_philo);
	philo_thread_join(philo, nb_philo);
	free(fork);
	printf("apres thread\n");
	return (0);
}

