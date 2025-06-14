/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:15:04 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/14 18:32:55 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "utils.h"

# ifndef LOGS
#  define LOGS false
# endif

#define LOG_STEP(...) do { if (LOGS) printf(__VA_ARGS__); } while (0)

# include <pthread.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_mutex
{
	char			*_name;
	bool			_is_set;
	pthread_mutex_t	_mutex;
}	t_mutex;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				_id;
	int				_total_meals;
	long			_time_to_start;
	pthread_t		_thread;

	//forks
	pthread_mutex_t	*_left_fork;
	pthread_mutex_t	*_right_fork;

	//last_meal
	long			_last_meal_time;
	t_mutex			_last_meal_mutex;

	//eat
	bool			_have_to_eat;
	t_mutex			_eat_mutex;

	t_data			*_data;
}	t_philo;

typedef struct s_data
{
	int				_philo_count;
	long			_time_to_die;
	long			_time_to_eat;
	long			_time_to_sleep;
	long			_number_of_times_each_philos_must_eat;
	//philosophers
	t_philo			**_philos;
	//forks
	t_mutex			*_forks;

	//stoped
	bool			_stopped;
	t_mutex			_stopped_mutex;
}	t_data;

bool	data_init(t_data **data, int ac, char **av);
bool	data_destroy(t_data *data);

bool	forks_init(t_data *data);
bool	forks_destroy(t_data *data);

bool	mutex_init(t_mutex *mutex, char *name);
bool	mutex_destroy(t_mutex *mutex);

bool	philos_init(t_data *data);
bool	philos_destroy(t_philo **philos);

#endif