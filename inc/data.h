/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:00:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/05/31 20:13:15 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "philo.h"
# include "utils.h"

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

#endif