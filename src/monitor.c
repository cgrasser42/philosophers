/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:19:23 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 00:55:23 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_philo_dead(t_data *data, int i)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&data->_philos[i]->_last_meal_mutex._mutex);
	if (current_time - data->_philos[i]->_last_meal_time >= data->_time_to_die)
	{
		pthread_mutex_lock(&data->_stopped_mutex._mutex);
		console_log(data->_philos[i], "died");
		data->_stopped = true;
		pthread_mutex_unlock(&data->_stopped_mutex._mutex);
		pthread_mutex_unlock(&data->_philos[i]->_last_meal_mutex._mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->_philos[i]->_last_meal_mutex._mutex);
	return (false);
}

static void	stop_simulation_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->_stopped_mutex._mutex);
	data->_stopped = true;
	pthread_mutex_unlock(&data->_stopped_mutex._mutex);
	printf("All philosophers have eaten\n");
}

bool	console_log(t_philo *philo, char *log)
{
	long	current_time;

	if (philo->_data->_stopped)
		return (false);
	current_time = get_time();
	printf("%-7ld %-4d %s\n", current_time
		- philo->_time_to_start, philo->_id, log);
	return (true);
}

void	monitor_simulation(t_data *data)
{
	int	i;
	int	count_eat;

	while (1)
	{
		i = 0;
		count_eat = 0;
		while (i < data->_philo_count)
		{
			if (is_philo_dead(data, i))
				return ;
			pthread_mutex_lock(&data->_philos[i]->_eat_mutex._mutex);
			if (data->_philos[i]->_have_to_eat)
				count_eat++;
			pthread_mutex_unlock(&data->_philos[i]->_eat_mutex._mutex);
			i++;
		}
		if (count_eat == data->_philo_count)
		{
			stop_simulation_all_ate(data);
			return ;
		}
	}
}
