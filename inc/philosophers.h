/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:08:51 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/05 19:49:47 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define USAGE "usage: <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"

# define USAGE_BONUS "<number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>"

# include "data.h"

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

bool	console_log(t_philo *philo, char *log);
void	*philosopher_life(void *arg);

long	get_time(void);
void	precise_sleep(long ms);
long	ft_atol(const char *str);
bool	str_is_numeric(char *str);

#endif