/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:20 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:48:13 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sim_runing(t_data *data)
{
	long	current_time;
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->_philo_count)
		{
			current_time = get_time();
			pthread_mutex_lock(&data->_philos[i]->_mutex_last_meal);
			if (current_time - data->_philos[i]->_last_meal_time
				>= data->_time_to_die)
			{
				pthread_mutex_lock(&data->_mutex_stopped);
				console_log(data->_philos[i], "died");
				data->_stopped = true;
				pthread_mutex_unlock(&data->_mutex_stopped);
				pthread_mutex_unlock(&data->_philos[i]->_mutex_last_meal);
				return ;
			}
			pthread_mutex_unlock(&data->_philos[i]->_mutex_last_meal);
			i++;
		}
	}
}

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
	data = data_new(av);
	if (!data)
		return (printf("Error\n"));
	i = 0;
	while (i < data->_philo_count)
	{
		pthread_create(&data->_philos[i]->_thread, NULL,
			philosopher_life, data->_philos[i]);
		i++;
	}
	precise_sleep(data->_time_to_die);
	sim_runing(data);
	i = 0;
	while (i < data->_philo_count)
		pthread_join(data->_philos[i++]->_thread, NULL);
	forks_destroy(data);
	mutex_destroy(data);
	philos_destroy(data->_philos);
	free(data);
	return (0);
}
