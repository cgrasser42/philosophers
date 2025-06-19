/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:03:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 00:38:13 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	console_log_mutex(t_philo *philo, char *log)
{
	bool	to_return;

	pthread_mutex_lock(&philo->_data->_stopped_mutex._mutex);
	to_return = console_log(philo, log);
	pthread_mutex_unlock(&philo->_data->_stopped_mutex._mutex);
	return (to_return);
}

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->_first_fork);
	if (!console_log_mutex(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->_first_fork);
		return (false);
	}
	if (philo->_data->_philo_count == 1)
	{
		pthread_mutex_unlock(philo->_first_fork);
		return (false);
	}
	pthread_mutex_lock(philo->_second_fork);
	if (!console_log_mutex(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->_second_fork);
		pthread_mutex_unlock(philo->_first_fork);
		return (false);
	}
	if (!console_log_mutex(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->_second_fork);
		pthread_mutex_unlock(philo->_first_fork);
		return (false);
	}
	return (true);
}

static bool	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (false);
	pthread_mutex_lock(&philo->_last_meal_mutex._mutex);
	philo->_last_meal_time = get_time();
	pthread_mutex_unlock(&philo->_last_meal_mutex._mutex);
	philo->_total_meals++;
	if (philo->_total_meals == philo->_data->_number_of_times_philos_must_eat)
	{
		pthread_mutex_lock(&philo->_eat_mutex._mutex);
		philo->_have_to_eat = true;
		pthread_mutex_unlock(&philo->_eat_mutex._mutex);
	}
	precise_sleep(philo->_data->_time_to_eat);
	pthread_mutex_unlock(philo->_second_fork);
	pthread_mutex_unlock(philo->_first_fork);
	return (true);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->_time_to_start = get_time();
	pthread_mutex_lock(&philo->_last_meal_mutex._mutex);
	philo->_last_meal_time = get_time();
	pthread_mutex_unlock(&philo->_last_meal_mutex._mutex);
	if (philo->_id % 2 == 0)
		precise_sleep(philo->_data->_time_to_eat / 2);
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
