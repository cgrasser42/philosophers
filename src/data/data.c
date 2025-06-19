/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:43:15 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:07:19 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	data_init(t_data **data, int ac, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!data)
		return (false);
	(*data)->_philo_count = ft_atol(av[0]);
	(*data)->_time_to_die = ft_atol(av[1]);
	(*data)->_time_to_eat = ft_atol(av[2]);
	(*data)->_time_to_sleep = ft_atol(av[3]);
	(*data)->_stopped = false;
	if (ac == 6)
		(*data)->_number_of_times_philos_must_eat = ft_atol(av[4]);
	else
		(*data)->_number_of_times_philos_must_eat = -1;
	if (LOGS)
		printf("data_init():\n");
	if (!mutex_init(&(*data)->_stopped_mutex, "_stopped_mutex")
		|| !forks_init(*data)
		|| !philos_init(*data))
		return (false);
	return (true);
}

bool	data_destroy(t_data *data)
{
	bool	all_data_destroy;

	if (!data)
		return (true);
	all_data_destroy = true;
	if (LOGS)
		printf("data_destroy():\n");
	all_data_destroy &= mutex_destroy(&data->_stopped_mutex);
	all_data_destroy &= philos_destroy(data->_philos);
	all_data_destroy &= forks_destroy(data);
	free(data);
	return (all_data_destroy);
}
