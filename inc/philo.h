/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:03:10 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/01 18:12:56 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philosophers.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				_id;
	int				_total_meals;
	long			_last_meal_time;
	pthread_t		_thread;
	pthread_mutex_t	*_left_fork;
	pthread_mutex_t	*_right_fork;
	t_data			*_data;
}	t_philo;

t_philo	*philo_new(t_data *data, int id,
			pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);

#endif