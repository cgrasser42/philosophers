/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:11:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:13:17 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	precise_sleep(long ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < ms)
		usleep(100);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sgn;
	long	to_return;

	i = 0;
	sgn = 1;
	to_return = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		to_return = to_return * 10 + (str[i] - 48);
		i++;
	}
	return (to_return * sgn);
}

bool	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
