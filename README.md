# Dining Philosophers Simulation

## Overview
This project is a multithreaded simulation of the classic Dining Philosophers problem implemented in C. It models philosophers who alternate between eating, thinking, and sleeping while competing for limited forks (mutexes). The program ensures synchronization and avoids deadlocks using mutexes and careful thread management.

## Features
* Configurable number of philosophers and simulation parameters via command-line arguments

* Thread-safe logging of philosopher actions with optional detailed logging for data structures

* Graceful handling of philosopher death and simulation termination

* Mutex wrappers with descriptive logging for easier debugging

* Precise timing control for philosopher actions (eat, sleep, think)

* Support for optional meal count limits per philosopher

## Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
* number_of_philosophers: Number of philosophers and forks (must be a positive integer)

* time_to_die: Time in milliseconds a philosopher can go without eating before dying

* time_to_eat: Time in milliseconds a philosopher spends eating

* time_to_sleep: Time in milliseconds a philosopher spends sleeping

* [number_of_times_each_philosopher_must_eat] (optional): If specified, the simulation ends when each philosopher has eaten this many times

## Example

```bash
./philo 5 800 200 200 7
```
Runs a simulation with 5 philosophers where each philosopher:
* Dies if they don't eat within 800 ms
* Eats for 200 ms
* Sleeps for 200 ms
* Stops the simulation after each philosopher has eaten at least 7 times

## Build Instructions

```bash
make          # Build the project normally  
make logs     # Build the project with detailed logging enabled for the data structure modules  
make clean    # Remove compiled object files  
make fclean   # Remove compiled objects and the executable  
make re       # Clean and rebuild the project
```

## Project Structure

```
.
├── src/
│   ├── main.c                # Program entry point and input validation
│   ├── monitor.c             # Simulation monitoring and death detection
│   ├── philosopher_life.c    # Philosopher thread routine
│   ├── utils.c               # Utility functions (e.g., time, string checks)
│   └── data/                 # Data structure management
│       ├── data.c            # Core data initialization and cleanup
│       ├── philo.c           # Philosopher data management
│       ├── mutex.c           # Mutex wrapper functions
│       └── fork.c            # Fork mutex initialization and destruction
├── inc/                      # Header files
│   ├── data.h
│   ├── philosophers.h
|   └── utils.h
├── Makefile                  # Build script
└── README.md                 # This file
```
## Important Notes
* The make logs target enables verbose logging specifically for the data structure modules (data.c, philo.c, mutex.c, fork.c) to aid debugging and provide insight into internal state changes.

* Input arguments must be numeric and valid. Invalid input will cause the program to exit with an error.

* Philosopher threads are synchronized to avoid deadlocks and race conditions.

* Mutexes are wrapped with custom structures that track their state and provide descriptive logging.

* Philosopher threads run concurrently, with even-numbered philosophers starting slightly delayed to reduce contention.

* The simulation stops either when a philosopher dies or when all philosophers have eaten the required number of times (if specified).


## Dependencies
* POSIX Threads (pthread)

* Standard C libraries (stdio.h, stdlib.h, unistd.h, sys/time.h)

## Author
cgrasser
