/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:53:05 by mbico             #+#    #+#             */
/*   Updated: 2024/07/30 20:23:28 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum e_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	mtx_fork;
}	t_fork;

typedef struct s_status
{
	t_bool			died;
	pthread_mutex_t	dmutex;
	pthread_mutex_t	print;

}	t_status;

typedef struct s_data
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	t_bool			alone;
	int				nb_meal;
	unsigned int	time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				hp;
	t_data			data;
	t_fork			*right;
	t_fork			*left;
	t_status		*status;
	pthread_t		thread;
}	t_philo;

//UTILS
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *nptr);
int				mutex_checker(int *nb, pthread_mutex_t *mutex);
void			mutex_set_int(int *var, int new, pthread_mutex_t *mutex);
void			mutex_printer(char *msg, t_philo *philo,
					unsigned int start_time);
unsigned int	time_now(void);
int				ft_strisint(char *str);
void			ft_putstr_fd(char *s, int fd);

//ACTION
t_bool			take_fork(t_philo *philo, unsigned int s_time, int nb_meal);
t_bool			eating(t_philo *philo, unsigned int s_time, int *nb_meal);
t_bool			thinking(t_philo *philo, unsigned int s_time, int nb_meal);
t_bool			waiting(t_philo *philo, unsigned int s_time, int nb_meal);
t_bool			sleeping(t_philo *philo, unsigned int s_time, int nb_meal);

//INIT
t_fork			*init_fork(int nb_philo);
t_data			init_data(char **argv, int argc);
void			init_status(t_status *status);
t_philo			*init_philo(t_data data, t_fork *fork, t_status *status,
					int nb_philo);

//MAIN
void			*routine(void *arg);
void			philo_thread_join(t_philo *philo, int nb_philo);
t_bool			someone_died(t_philo *philo, unsigned int s_time,
					int nb_meal);

#endif
