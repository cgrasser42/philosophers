/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:13:54 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:48:25 by cgrasser         ###   ########.fr       */
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
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i > -1)
				pthread_mutex_destroy(&forks[i]);
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
	free(data->_forks);
}
