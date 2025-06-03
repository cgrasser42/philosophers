/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:03:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/03 18:23:46 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	console_log(t_philo *philo, char *log)
{
	long	current_time;

	pthread_mutex_lock(&philo->_data->_mutex_stopped);
	if (philo->_data->_stopped)
	{
		pthread_mutex_unlock(&philo->_data->_mutex_stopped);
		return (false);
	}
	current_time = get_time();
	printf("%-7ld %-4d %s\n", current_time
		- philo->_time_to_start, philo->_id, log);
	pthread_mutex_unlock(&philo->_data->_mutex_stopped);
	return (true);
}

static bool	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->_left_fork);
	if (!console_log(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->_left_fork), false);
	if (philo->_data->_philo_count == 1)
		return (false);
	pthread_mutex_lock(philo->_right_fork);
	if (!console_log(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->_left_fork),
			pthread_mutex_unlock(philo->_right_fork), false);
	if (!console_log(philo, "is eating"))
		return (pthread_mutex_unlock(philo->_left_fork),
			pthread_mutex_unlock(philo->_right_fork), false);
	philo->_last_meal_time = get_time();
	philo->_total_meals++;
	precise_sleep(philo->_data->_time_to_eat);
	pthread_mutex_unlock(philo->_right_fork);
	pthread_mutex_unlock(philo->_left_fork);
	return (true);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->_last_meal_time = get_time();
	philo->_time_to_start = get_time();
	if (philo->_id % 2 == 0)
		precise_sleep(philo->_data->_time_to_eat);
	while (true)
	{
		if (!eat(philo))
			break ;
		if (!console_log(philo, "is sleeping"))
			break ;
		precise_sleep(philo->_data->_time_to_sleep);
		if (!console_log(philo, "is thinking"))
			break ;
	}
	return (NULL);
}

t_philo	*philo_new(t_data *data, int id,
	pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->_id = id;
	philo->_data = data;
	philo->_left_fork = left_fork;
	philo->_right_fork = right_fork;
	return (philo);
}
