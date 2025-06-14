/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:43:15 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/14 17:59:11 by cgrasser         ###   ########.fr       */
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
		(*data)->_number_of_times_each_philos_must_eat = ft_atol(av[4]);
	else
		(*data)->_number_of_times_each_philos_must_eat = -1;
	if (!forks_init(*data) || !philos_init(*data))
		return (false);
	return (true);
}

bool	data_destroy(t_data *data)
{
	bool	all_data_destroy;

	if (!data)
		return (true);
	all_data_destroy = true;
	if (!philos_destroy(data->_philos))
		all_data_destroy = false;
	if (!forks_destroy(data))
		all_data_destroy = false;
	free(data);
	return (all_data_destroy);
}
