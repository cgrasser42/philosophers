/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:00:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/01 18:39:18 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "philosophers.h"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				_philo_count;
	long			_time_to_die;
	long			_time_to_eat;
	long			_time_to_sleep;
	t_philo			**_philos;
	pthread_mutex_t	*_forks;
}	t_data;

t_data	*data_new(char **av);
void	forks_destroy(t_data *data);
void	philos_destroy(t_philo **philos);

#endif