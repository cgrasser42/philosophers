/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:15:04 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:50:17 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				_id;
	int				_total_meals;
	long			_last_meal_time;
	pthread_mutex_t	_mutex_last_meal;
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
	bool			_stopped;
}	t_data;

t_data			*data_new(char **av);
// void			data_destroy(t_data *data); 

pthread_mutex_t	*forks_init(t_data *data);
void			forks_destroy(t_data *data);

t_philo			**philos_init(t_data *data);
void			philos_destroy(t_philo **philos);

void			mutex_destroy(t_data *data);

#endif