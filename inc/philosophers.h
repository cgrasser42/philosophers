/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:08:51 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:11:13 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/**
 * @file philosophers.h
 * @brief Header file for the Dining Philosophers simulation.
 *
 * Declares core routines for the philosopher threads and simulation monitor.
 */

/**
 * @def USAGE
 * @brief CLI usage message for the philosophers
 * simulation (mandatory arguments).
 */
# define USAGE "usage: <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"

/**
 * @def USAGE_BONUS
 * @brief CLI usage message for the philosophers simulation
 * with optional eating limit.
 */
# define USAGE_BONUS "<number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>"

# include "data.h"

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/**
 * @brief Logs a philosopher's action to the console.
 *
 * If the simulation is stopped, the function does nothing and returns false.
 * Otherwise, it prints the current timestamp (relative to the start of
 * the simulation), philosopher ID, and the provided message.
 *
 * @param philo Pointer to the philosopher performing the action.
 * @param log Message describing the action.
 * @return true if the message was printed, false if the simulation has stopped.
 */
bool	console_log(t_philo *philo, char *log);

/**
 * @brief Monitors the state of the simulation to detect
 * philosopher death or completion.
 *
 * This function runs in a loop and checks two main conditions:
 * 1. If any philosopher has died (hasn't eaten within `time_to_die`),
 * the simulation is stopped.
 * 2. If all philosophers have eaten the required number of times,
 * the simulation is stopped.
 *
 * It checks each philosopher's last meal time and whether they have completed
 * their meals, using mutexes to ensure thread-safe access to shared data.
 *
 * @param data Pointer to the shared simulation data structure.
 */
void	monitor_simulation(t_data *data);

/**
 * @brief Thread routine representing the life of a philosopher.
 *
 * This function simulates the life cycle of a philosopher in the classic
 * Dining Philosophers problem. Each philosopher repeatedly performs the actions:
 * eating, sleeping, and thinking, until a stopping condition is met (e.g., 
 * a philosopher dies or all required meals are completed).
 *
 * The function also initializes the start time and the last
 * meal time for the philosopher.
 * Even-numbered philosophers delay their start slightly to reduce contention.
 * 
 * Thread-safe logging and resource (forks) access are ensured using mutexes.
 *
 * @param arg A pointer to a t_philo structure representing the philosopher.
 * @return NULL when the thread exits.
 */
void	*philosopher_life(void *arg);

#endif