/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:03:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:49:37 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	console_log_mutex(t_philo *philo, char *log)
{
	bool	to_return;

	pthread_mutex_lock(&philo->_data->_mutex_stopped);
	to_return = console_log(philo, log);
	pthread_mutex_unlock(&philo->_data->_mutex_stopped);
	return (to_return);
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

static bool	eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->_left_fork < philo->_right_fork)
	{
		first = philo->_left_fork;
		second = philo->_right_fork;
	}
	else
	{
		first = philo->_right_fork;
		second = philo->_left_fork;
	}
	pthread_mutex_lock(first);
	if (!console_log_mutex(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	if (philo->_data->_philo_count == 1)
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	pthread_mutex_lock(second);
	if (!console_log_mutex(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (false);
	}
	if (!console_log_mutex(philo, "is eating"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (false);
	}
	pthread_mutex_lock(&philo->_mutex_last_meal);
	philo->_last_meal_time = get_time();
	pthread_mutex_unlock(&philo->_mutex_last_meal);
	philo->_total_meals++;
	precise_sleep(philo->_data->_time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (true);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->_mutex_last_meal);
	philo->_last_meal_time = get_time();
	pthread_mutex_unlock(&philo->_mutex_last_meal);
	philo->_time_to_start = get_time();
	if (philo->_id % 2 == 0)
		precise_sleep(philo->_data->_time_to_eat);
	while (true)
	{
		if (!eat(philo))
			break ;
		if (!console_log_mutex(philo, "is sleeping"))
			break ;
		precise_sleep(philo->_data->_time_to_sleep);
		if (!console_log_mutex(philo, "is thinking"))
			break ;
	}
	return (NULL);
}
