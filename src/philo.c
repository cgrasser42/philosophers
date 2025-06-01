/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:03:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/01 18:19:55 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(t_data *data, int id,
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
