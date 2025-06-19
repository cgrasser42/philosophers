/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:15:04 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/20 01:08:55 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/**
 * @file data.h
 * @brief Data structures, macros, and function declarations
 * for the philosopher simulation.
 *
 * This header defines the core data types, mutex wrappers,
 * macros for logging messages, and function prototypes used throughout
 * the philosopher simulation program.
 */

# include "utils.h"

# include <pthread.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

# ifndef LOGS
#  define LOGS false /**< Enable or disable logging globally*/
# endif

/**
 * @def INIT_SUCCESS
 * @brief Log message for successful initialization.
 */
# define INIT_SUCCESS	"initialized successfully"

/**
 * @def INVALID_ATTR
 * @brief Log message for mutex initialization failure due to invalid attributes.
 */
# define INVALID_ATTR	"failed to initialize (invalid attributes)"

/**
 * @def NO_MEMORY
 * @brief Log message for mutex initialization failure
 * due to insufficient memory.
 */
# define NO_MEMORY		"failed to initialize (not enough memory)"

/**
 * @def RESOURCE_LIMIT
 * @brief Log message for mutex initialization failure
 * due to system resource limits.
 */
# define RESOURCE_LIMIT	"failed to initialize (system resource limit reached)"

/**
 * @def NO_PERMISSION
 * @brief Log message for mutex initialization failure
 * due to insufficient permissions.
 */
# define NO_PERMISSION	"failed to initialize (insufficient permissions)"

/**
 * @def UNKNOWN
 * @brief Log message for mutex initialization failure
 * due to unknown error.
 */
# define UNKNOWN		"failed to initialize (unknown error code %d)"

/**
 * @def DESTROY_SUCCESS
 * @brief Log message for successful mutex destruction.
 */
# define DESTROY_SUCCESS "destroyed successfully"

/**
 * @def DESTROY_IN_USE
 * @brief Log message for mutex destruction failure
 * due to mutex being in use.
 */
# define DESTROY_IN_USE	 "is still locked or in use"

/**
 * @def DESTROY_INVALID
 * @brief Log message for mutex destruction failure
 * due to invalid mutex.
 */
# define DESTROY_INVALID "is invalid or not properly initialized"

/**
 * @def DESTROY_UNKNOWN
 * @brief Log message for mutex destruction failure
 * due to unknown error.
 */
# define DESTROY_UNKNOWN "failed to destroy (unknown error code %d)"

/**
 * @brief Forward declaration of the s_data structure.
 *
 * This allows the use of pointers to t_data in structures (like t_philo)
 * that are defined before the full definition of s_data is available.
 */
typedef struct s_data	t_data;

/**
 * @struct s_mutex
 * @brief Wrapper for pthread mutex with additional metadata for logging.
 *
 * Stores the actual pthread_mutex_t, a boolean to track initialization status,
 * and a name used for descriptive logging.
 */
typedef struct s_mutex
{
	char			*_name; /**< Name of the mutex for logging purposes */
	bool			_is_set; /**< Indicates whether the mutex is initialized */
	pthread_mutex_t	_mutex; /**< The underlying pthread mutex */
}	t_mutex;

/**
 * @struct s_philo
 * @brief Philosopher structure containing simulation
 * state and synchronization primitives.
 *
 * Contains information such as philosopher ID, number of meals eaten,
 * timing info, thread handle, forks pointers, mutexes for last
 * meal and eating state, and a back-reference to the shared data.
 */
typedef struct s_philo
{
	int				_id; /**< Philosopher identifier */
	int				_total_meals; /**< Number of meals eaten */
	long			_time_to_start; /**< Timestamp for simulation start */
	pthread_t		_thread; /**< Thread representing the philosopher */
	pthread_mutex_t	*_first_fork; /**< Pointer to first fork mutex */
	pthread_mutex_t	*_second_fork; /**< Pointer to second fork mutex */
	long			_last_meal_time; /**< Timestamp of last meal */
	t_mutex			_last_meal_mutex; /**< Mutex protecting last meal time */
	bool			_have_to_eat; /**< Flag to indicate if needs to eat */
	t_mutex			_eat_mutex; /**< Mutex protecting eating state */
	t_data			*_data; /**< Pointer to shared simulation data */
}	t_philo;

/**
 * @struct s_data
 * @brief Global simulation configuration and shared state.
 *
 * Contains simulation parameters, philosopher array, forks mutex array,
 * and control variables for stopping the simulation.
 */
typedef struct s_data
{
	int		_philo_count; /**< Total number of philosophers */
	long	_time_to_die; /**< Time in ms before a philosopher dies */
	long	_time_to_eat; /**< Time in ms to eat */
	long	_time_to_sleep; /**< Time in ms to sleep */
	long	_number_of_times_philos_must_eat; /**< Optional meal count limit */
	t_philo	**_philos; /**< Array of pointers to philosopher structures */
	t_mutex	*_forks; /**< Array of fork mutex wrappers */
	bool	_stopped; /**< Flag to indicate if simulation stopped */
	t_mutex	_stopped_mutex; /**< Mutex protecting stopped flag */
}	t_data;

/**
 * @brief Initializes the simulation data structure.
 *
 * Allocates and initializes a t_data structure based on command-line arguments.
 * Parses philosopher configuration, initializes forks and philosophers.
 *
 * @param data A pointer to the pointer of the t_data structure to initialize.
 * @param ac Argument count (from main).
 * @param av Argument values (array of strings from main,
 * containing simulation parameters).
 *            - av[0] = number of philosophers
 *            - av[1] = time to die
 *            - av[2] = time to eat
 *            - av[3] = time to sleep
 *            - av[4] = (optional) number of times each philosopher must eat
 * @return true if all data was initialized successfully, false otherwise.
 *
 * @note If initialization fails at any step,
 * allocated memory should be freed externally if needed.
 */
bool	data_init(t_data **data, int ac, char **av);

/**
 * @brief Frees and destroys all dynamically allocated simulation data.
 *
 * Calls cleanup functions for philosophers and forks, and frees the main
 * data structure. Ensures that all components are properly destroyed.
 *
 * @param data Pointer to the t_data structure to destroy. Can be NULL.
 * @return true if all internal components were destroyed successfully,
 * false otherwise.
 */
bool	data_destroy(t_data *data);

/**
 * @brief Initializes the mutexes representing the forks.
 *
 * Allocates memory for the fork mutex array based on the number of philosophers
 * and initializes each mutex using `mutex_init`.
 * Logs progress if LOGS is enabled.
 *
 * @param data Pointer to the global data structure
 * containing simulation configuration.
 * @return true if all fork mutexes were successfully initialized,
 * false if allocation or initialization fails.
 *
 * @note The mutexes are named "_fork_mutex" for identification in logs.
 */
bool	forks_init(t_data *data);

/**
 * @brief Destroys all fork mutexes and frees the allocated array.
 *
 * Iterates through all fork mutexes and attempts
 * to destroy each using `mutex_destroy`.
 * Logs each destruction if LOGS is enabled.
 * Frees the memory allocated for forks.
 *
 * @param data Pointer to the global data structure containing the fork mutexes.
 * @return true if all mutexes were successfully destroyed,
 * false if any destruction fails.
 */
bool	forks_destroy(t_data *data);

/**
 * @brief Initializes a mutex with a given name for logging.
 *
 * Wraps the pthread_mutex_init function and assigns a descriptive name
 * to the mutex for easier debugging and logging. Logs success or error messages
 * based on the result of the initialization if LOGS is enabled.
 *
 * @param mutex Pointer to the t_mutex structure to initialize.
 * @param name A string used to identify the mutex in log messages.
 * @return true if the mutex was successfully initialized, false otherwise.
 */
bool	mutex_init(t_mutex *mutex, char *name);

/**
 * @brief Destroys a previously initialized mutex.
 *
 * Wraps the pthread_mutex_destroy function and logs the destruction status.
 * Ensures the mutex is only destroyed if it was successfully initialized.
 * If the mutex name is not set, defaults to "Unknown mutex" for logging.
 *
 * @param mutex Pointer to the t_mutex structure to destroy.
 * @return true if the mutex was successfully destroyed
 * or was not initialized, false otherwise.
 */
bool	mutex_destroy(t_mutex *mutex);

/**
 * @brief Initializes philosopher structures and their associated mutexes.
 *
 * Allocates memory for philosopher pointers array and initializes each
 * philosopher using `philo_new`. For each philosopher, also initializes mutexes
 * for tracking last meal time and eating state.
 * Logs progress if LOGS is enabled.
 *
 * @param data Pointer to the global data structure
 * containing simulation parameters.
 * @return true if all philosophers and their mutexes were
 * initialized successfully, false if any allocation or initialization failed.
 *
 * @note The philosophers array is null-terminated for easier iteration.
 */
bool	philos_init(t_data *data);

/**
 * @brief Frees philosopher structures and destroys their associated mutexes.
 *
 * Iterates through the null-terminated array of philosopher pointers, destroys
 * each philosopher's mutexes (_last_meal_mutex and _eat_mutex),
 * frees the philosopher memory, and finally frees the philosophers
 * array itself. Logs progress if LOGS is enabled.
 *
 * @param philos Null-terminated array of philosopher pointers to destroy.
 * @return true if all mutexes were successfully destroyed,
 * false if any destruction failed.
 *
 * @note If philos is NULL, the function returns true immediately.
 */
bool	philos_destroy(t_philo **philos);

#endif