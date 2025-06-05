/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:19:57 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:49:25 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static t_philo	*philo_new(t_data *data, int id,
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

t_philo	**philos_init(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * (data->_philo_count + 1));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->_philo_count)
	{
		philos[i] = philo_new(data, i + 1, &data->_forks[i],
				&data->_forks[(i + 1) % data->_philo_count]);
		if (!philos[i])
			return (philos_destroy(philos), NULL);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

void	philos_destroy(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
		free(philos[i++]);
	free(philos);
}
