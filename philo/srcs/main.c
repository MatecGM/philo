/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:00:03 by mbico             #+#    #+#             */
/*   Updated: 2024/08/20 16:32:23 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

t_bool	arg_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("arg error : ./philo [nb_philo] [time_die] [time_eat]\
 [time_sleep] optional : [nb_meal]\n", 2);
		return (TRUE);
	}
	else if (!ft_strisint(argv[1]) || !ft_strisint(argv[2])
		|| !ft_strisint(argv[3]) || !ft_strisint(argv[4])
		|| (argc == 6 && !ft_strisint(argv[5])))
	{
		ft_putstr_fd("arg error : args need to be of [int] type\n", 2);
		return (TRUE);
	}
	else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
	{
		ft_putstr_fd("arg error : the number of philosopher must be between\
 1 and 200] included\n", 2);
		return (TRUE);
	}
	else if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		ft_putstr_fd("arg error : args need to be greater than 0\n", 2);
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

	if (arg_error(argc, argv))
		return (1);
	nb_philo = ft_atoi(argv[1]);
	data = init_data(argv, argc);
	fork = init_fork(nb_philo);
	if (!fork)
		return (1);
	if (init_status(status, argv[1]))
		return (1);
	philo = init_philo(data, fork, status, nb_philo);
	if (!philo)
	{
		free(fork);
		free(status->mealcount);
		return (1);
	}
	philo_thread_join(philo, nb_philo, fork, status);
	return (0);
}
