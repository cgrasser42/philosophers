/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:09:03 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/15 01:17:04 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	mutex_init(t_mutex *mutex, char *name)
{
	int	result;

	mutex->_name = name;
	result = pthread_mutex_init(&mutex->_mutex, NULL);
	mutex->_is_set = (result == 0);
	if (LOGS)
	{
		if (result == 0)
			printf("Success: %s" INIT_SUCCESS"\n", mutex->_name);
		else if (result == EINVAL)
			printf("Error: %s" INVALID_ATTR"\n", mutex->_name);
		else if (result == ENOMEM)
			printf("Error: %s" NO_MEMORY"\n", mutex->_name);
		else if (result == EAGAIN)
			printf("Error: %s" RESOURCE_LIMIT"\n", mutex->_name);
		else if (result == EPERM)
			printf("Error: %s" NO_PERMISSION"\n", mutex->_name);
		else
			printf("Error: %s" UNKNOWN"\n", mutex->_name, result);
	}
	return (mutex->_is_set);
}

bool	mutex_destroy(t_mutex *mutex)
{
	int	result;

	if (!mutex->_is_set)
		return (true);
	if (!mutex->_name)
		mutex->_name = "Unknown mutex";
	result = pthread_mutex_destroy(&mutex->_mutex);
	mutex->_is_set = (result == 0);
	if (LOGS)
	{
		if (result == 0)
			printf("Success: %s" DESTROY_SUCCESS"\n", mutex->_name);
		else if (result == EBUSY)
			printf("Error: %s" DESTROY_IN_USE"\n", mutex->_name);
		else if (result == EINVAL)
			printf("Error: %s" DESTROY_INVALID"\n", mutex->_name);
		else
			printf("Error: %s" DESTROY_UNKNOWN"\n", mutex->_name, result);
	}
	return (!mutex->_is_set);
}
