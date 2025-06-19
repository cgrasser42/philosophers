/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:40:35 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:12:48 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * @file utils.h
 * @brief Utility functions used throughout the philosopher simulation.
 *
 * This file declares timing, string, and logging utility functions used
 * to support the core simulation logic.
 * These functions help with time measurement, sleep accuracy,
 * input validation, and thread-safe logging.
 */

# include <stdbool.h>

/**
 * @brief Gets the current time in milliseconds.
 *
 * Uses `gettimeofday` to retrieve the system time
 * and converts it to milliseconds.
 *
 * @return The current time in milliseconds since the Unix epoch.
 */
long	get_time(void);

/**
 * @brief Sleeps for a specified duration with millisecond precision.
 *
 * This function uses a busy-wait loop and short `usleep` calls to achieve
 * more accurate sleep durations than standard `usleep` or `sleep` might allow.
 *
 * @param ms Duration to sleep in milliseconds.
 */
void	precise_sleep(long ms);

/**
 * @brief Converts a string to a long integer.
 *
 * Similar to the standard `atol` function, this implementation handles optional
 * leading whitespace, a sign character, and digits.
 *
 * @param str Null-terminated string representing a number.
 * @return The converted long integer.
 */
long	ft_atol(const char *str);

/**
 * @brief Checks whether a string consists entirely of digits.
 *
 * This function returns true only if every character in the string is
 * between '0' and '9'. It does not handle negative signs or whitespace.
 *
 * @param str The string to check.
 * @return true if the string is numeric, false otherwise.
 */
bool	str_is_numeric(char *str);

#endif