/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:43:15 by cgrasser          #+#    #+#             */
/*   Updated: 2025/05/31 21:41:16 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

pthread_mutex_t	*forks_init(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->_philo_count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->_philo_count)
	{
		if (pthread_mutex_init(&data->_forks[i++], NULL) != 0)
		{
			while (--i > -1)
				pthread_mutex_destroy(&data->_forks[i]);
			return (free(forks), NULL);
		}
		i++;
	}
	return (forks);
}

void	forks_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->_philo_count)
		pthread_mutex_destroy(&data->_forks[i++]);
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
			return (free_tab(philos), NULL);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

t_data	*data_new(char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->_philo_count = ft_atol(av[0]);
	data->_forks = forks_init(data);
	if (!data->_forks)
		return (free(data), NULL);
	data->_philos = philos_init(data);
	if (!data->_philos)
		return (forks_destroy(data), free(data), NULL);
	data->_time_to_die = ft_atol(av[1]);
	data->_time_to_eat = ft_atol(av[2]);
	data->_time_to_sleep = ft_atol(av[3]);
	return (data);
}
