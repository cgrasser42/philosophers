/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:19:57 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/14 18:15:26 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static t_philo	*philo_new(t_data *data, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->_id = id;
	philo->_data = data;
	philo->_left_fork = &data->_forks[id - 1]._mutex;
	philo->_right_fork = &data->_forks[id % data->_philo_count]._mutex;
	philo->_total_meals = 0;
	philo->_have_to_eat = false;
	return (philo);
}

bool	philos_init(t_data *data)
{
	int		i;

	data->_philos = malloc(sizeof(t_philo *) * (data->_philo_count + 1));
	if (!data->_philos)
		return (false);
	i = 0;
	LOG_STEP("\nphilos_init() =>\n");
	while (i < data->_philo_count)
	{
		LOG_STEP("_philos[%3d] =>\n", i);
		data->_philos[i] = philo_new(data, i + 1);
		if (!data->_philos[i]
			|| !mutex_init(&data->_philos[i]->_last_meal_mutex, "_last_meal_mutex")
			|| !mutex_init(&data->_philos[i]->_eat_mutex, "_eat_mutex"))
			return (false);
		i++;
	}
	data->_philos[i] = NULL;
	return (true);
}

bool	philos_destroy(t_philo **philos)
{
	bool	all_mutexes_destroyed;
	int		i;

	if (!philos)
		return (true);
	all_mutexes_destroyed = true;
	i = 0;
	LOG_STEP("\nphilos_destroy() =>\n");
	while (philos[i])
	{
		LOG_STEP("_philos[%3d] =>\n", i);
		if (!mutex_destroy(&philos[i]->_last_meal_mutex))
			all_mutexes_destroyed = false;
		if (!mutex_destroy(&philos[i]->_eat_mutex))
			all_mutexes_destroyed = false;
		free(philos[i++]);
	}
	free(philos);
	return (all_mutexes_destroyed);
}
