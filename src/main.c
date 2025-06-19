/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:20 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:13:04 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_input(int ac, char *av[])
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("%s\n", USAGE);
		printf("%119s\n", USAGE_BONUS);
		return (false);
	}
	i = 0;
	while (av[i])
	{
		if (!str_is_numeric(av[i++]))
		{
			printf("Error: invalid argument — digits only expected \n");
			return (false);
		}
	}
	return (true);
}

int	main(int ac, char *av[])
{
	t_data	*data;
	int		i;

	if (!check_input(ac, ++av))
		return (1);
	if (!data_init(&data, ac, av))
	{
		data_destroy(data);
		return (1);
	}
	i = 0;
	while (i < data->_philo_count)
	{
		data->_philos[i]->_time_to_start = get_time();
		data->_philos[i]->_last_meal_time = get_time();
		pthread_create(&data->_philos[i]->_thread, NULL,
			philosopher_life, data->_philos[i]);
		i++;
	}
	monitor_simulation(data);
	i = 0;
	while (i < data->_philo_count)
		pthread_join(data->_philos[i++]->_thread, NULL);
	data_destroy(data);
	return (0);
}
