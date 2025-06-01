/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:08:51 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/01 18:15:03 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define USAGE "usage: <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"

# define USAGE_BONUS "<number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>"

# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# include "data.h"
# include "philo.h"
# include "utils.h"

#endif