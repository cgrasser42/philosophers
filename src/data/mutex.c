/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:09:03 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/14 18:14:56 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	mutex_init(t_mutex *mutex, char *name)
{
	int	result;

	mutex->_name = name;
	result = pthread_mutex_init(&mutex->_mutex, NULL);
	if (result == 0)
	{
		mutex->_is_set = true;
		LOG_STEP("Success: %s initialized successfully\n", mutex->_name);
		return (true);
	}
	else if (result == EINVAL)
		LOG_STEP("Error: %s failed to initialize (invalid attributes)\n", mutex->_name);
	else if (result == ENOMEM)
		LOG_STEP("Error: %s failed to initialize (not enough memory)\n", mutex->_name);
	else if (result == EAGAIN)
		LOG_STEP("Error: %s failed to initialize (system resource limit reached)\n", mutex->_name);
	else if (result == EPERM)
		LOG_STEP("Error: %s failed to initialize (insufficient permissions)\n", mutex->_name);
	else
		LOG_STEP("Error: %s failed to initialize (unknown error code %d)\n", mutex->_name, result);
	mutex->_is_set = false;
	return (false);
}

bool	mutex_destroy(t_mutex *mutex)
{
	int	result;

	if (!mutex->_is_set)
		return (true);
	if (!mutex->_name)
		mutex->_name = "Unknown mutex";
	result = pthread_mutex_destroy(&mutex->_mutex);
	if (result == 0)
	{
		mutex->_is_set = false;
		LOG_STEP("Success: %s destroyed successfully\n", mutex->_name);
		return (true);
	}
	else if (result == EBUSY)
		LOG_STEP("Error: %s is still locked or in use\n", mutex->_name);
	else if (result == EINVAL)
		LOG_STEP("Error: %s is invalid or not properly initialized\n", mutex->_name);
	else
		LOG_STEP("Error: %s failed to destroy (unknown error code %d)\n", mutex->_name, result);
	return (false);
}
