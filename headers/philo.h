/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:53:05 by mbico             #+#    #+#             */
/*   Updated: 2024/07/21 21:49:45 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef	enum	e_bool 
{
	ERROR = -1,
	FALSE,
	TRUE,
}	t_bool;

typedef	struct	s_fork
{
	pthread_mutex_t	left;
	pthread_mutex_t	right;
}	t_fork;


typedef	struct	s_status
{
	t_bool			died;
	pthread_mutex_t	mutex;
}	t_status;

typedef struct	s_data
{
	int			time_die;
	int			time_eat;
	int			time_sleep;
}	t_data;

typedef struct s_philo
{
	int			id;
	t_data		data;
	t_fork		fork;
	t_status	status;
}	t_philo;

//UTILS

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);

#endif
