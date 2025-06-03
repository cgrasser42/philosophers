/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:08:51 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/03 18:24:45 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define USAGE "usage: <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"

# define USAGE_BONUS "<number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>"

# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				_id;
	int				_total_meals;
	long			_last_meal_time;
	long			_time_to_start;
	pthread_t		_thread;
	pthread_mutex_t	*_left_fork;
	pthread_mutex_t	*_right_fork;
	t_data			*_data;
}	t_philo;

typedef struct s_data
{
	int				_philo_count;
	long			_time_to_die;
	long			_time_to_eat;
	long			_time_to_sleep;
	t_philo			**_philos;
	pthread_mutex_t	*_forks;
	pthread_mutex_t	_mutex_stopped;
	pthread_mutex_t	_mutex_log;
	bool			_stopped;
}	t_data;

t_data	*data_new(char **av);
void	forks_destroy(t_data *data);
void	philos_destroy(t_philo **philos);

t_philo	*philo_new(t_data *data, int id,
			pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);

bool	console_log(t_philo *philo, char *log);
void	*philosopher_life(void *arg);

long	get_time(void);
void	precise_sleep(long ms);
long	ft_atol(const char *str);
bool	str_is_numeric(char *str);

#endif