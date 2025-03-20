# Philosophers 42

## Overview
Philosophers 42 is a simulation project that solves the famous "Dining Philosophers Problem" - a classic synchronization and concurrency challenge in computer science. This implementation focuses on understanding resource sharing, deadlock prevention, and process synchronization using threads and mutexes.

## The Problem
Five philosophers sit at a round table with five forks placed between them. Each philosopher alternates between thinking and eating. To eat, a philosopher needs two forks - one from their left and one from their right. The challenge is to design a concurrent algorithm that allows the philosophers to eat without causing deadlocks or resource starvation.

## Features
- Multi-threaded implementation of the dining philosophers problem
- Deadlock prevention using resource hierarchy
- Configurable number of philosophers (default: 5)
- Detailed logging of events and state changes
- Configurable time limits for eating, thinking, and maximum simulation time

## Requirements
- C compiler (gcc recommended)
- pthread library
- Make

## Installation
```bash
git clone https://github.com/yourusername/philosophers-42.git
cd philosophers-42
make
```

## Usage
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: Number of philosophers and forks (default: 5)
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
- `time_to_eat`: Time in milliseconds that a philosopher spends eating
- `time_to_sleep`: Time in milliseconds that a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) If specified, the simulation stops when all philosophers have eaten this many times

### Example
```bash
./philo 5 800 200 200 5
```
This runs the simulation with 5 philosophers, each dying if they don't eat for 800ms, taking 200ms to eat, 200ms to sleep, and the simulation stops when each philosopher has eaten 5 times.

## Implementation Details
The project implements the dining philosophers problem using threads and mutexes:

- Each philosopher is represented by a thread
- Each fork is protected by a mutex
- A monitoring mechanism checks if philosophers are dying
- Timestamp-based logging shows the state of each philosopher

## Rules
- Each philosopher should be a thread
- There is one fork between each philosopher, so for N philosophers there are N forks
- A philosopher must take the fork on their right and left to eat
- A philosopher must eat, sleep, and think in order
- If a philosopher doesn't start eating within `time_to_die` milliseconds since their last meal or the beginning of the simulation, they die
- Messages display state changes with timestamps: `timestamp_in_ms X has taken a fork`, `timestamp_in_ms X is eating`, etc.
- The simulation stops when a philosopher dies or when all philosophers have eaten `number_of_times_each_philosopher_must_eat` times

## Project Structure
```
.
├── include/             # Header files
│   └── philosophers.h   # Main header file
├── src/                 # Source files
│   ├── main.c           # Entry point
│   ├── init.c           # Initialization functions
│   ├── philosophers.c   # Core philosopher logic
│   ├── utils.c          # Utility functions
│   └── monitor.c        # Death monitoring
├── Makefile             # Build script
└── README.md            # This file
```

## Handling the Edge Cases
- When there is only one philosopher, they will die as they cannot acquire two forks
- The program handles invalid inputs gracefully
- All memory allocated is properly freed before the program exits
- Race conditions are carefully managed with mutex protections

## Learning Objectives
- Multithreading concepts
- Resource sharing and synchronization
- Deadlock prevention
- Race condition handling
- Performance optimization in concurrent environments

## Resources
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Concurrent Programming Concepts](https://www.cs.cmu.edu/~410/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements
This project was completed as part of the 42 programming curriculum.
