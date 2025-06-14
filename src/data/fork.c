/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:33:09 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/14 18:07:05 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	forks_init(t_data *data)
{
	int	i;

	data->_forks = malloc(sizeof(t_mutex) * data->_philo_count);
	if (!data->_forks)
		return (false);
	i = 0;
	LOG_STEP("forks_init() =>\n");
	while (i < data->_philo_count)
	{
		LOG_STEP("_forks[%3d] => ", i);
		if (!mutex_init(&data->_forks[i], "_fork_mutex"))
			return (false);
		i++;
	}
	return (true);
}

bool	forks_destroy(t_data *data)
{
	bool	all_mutexes_destroyed;
	int		i;

	if (!data->_forks)
		return (true);
	all_mutexes_destroyed = true;
	i = 0;
	LOG_STEP("\nforks_destroy():\n");
	while (i < data->_philo_count)
	{
		LOG_STEP("_forks[%3d] => ", i);
		if (!mutex_destroy(&data->_forks[i]))
			all_mutexes_destroyed = false;
		i++;
	}
	free(data->_forks);
	return (all_mutexes_destroyed);
}
