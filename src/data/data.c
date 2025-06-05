/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:43:15 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:48:57 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->_mutex_stopped, NULL) != 0)
	{
		return (false);
	}
	i = 0;
	while (i < data->_philo_count)
	{
		if (pthread_mutex_init(&data->_philos[i]->_mutex_last_meal, NULL) != 0)
		{
			while (--i > -1)
				pthread_mutex_destroy(&data->_philos[i]->_mutex_last_meal);
			pthread_mutex_destroy(&data->_mutex_stopped);
			return (false);
		}
		i++;
	}
	return (true);
}

void	mutex_destroy(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->_mutex_stopped);
	i = 0;
	while (i < data->_philo_count)
		pthread_mutex_destroy(&data->_philos[i++]->_mutex_last_meal);
}

t_data	*data_new(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->_philo_count = ft_atol(av[0]);
	data->_forks = forks_init(data);
	if (!data->_forks)
		return (free(data), NULL);
	data->_philos = philos_init(data);
	if (!data->_philos)
		return (forks_destroy(data), free(data), NULL);
	data->_time_to_die = ft_atol(av[1]);
	data->_time_to_eat = ft_atol(av[2]);
	data->_time_to_sleep = ft_atol(av[3]);
	mutex_init(data);
	return (data);
}
