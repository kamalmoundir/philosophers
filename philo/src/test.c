/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:22:56 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 16:28:27 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>

#include "../include/philo.h"

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (!philo->table->end_time) {
        // Thinking
        printf("Philosopher %d is thinking\n", philo->id);

        // Picking up forks
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);

        // Eating
        printf("Philosopher %d is eating\n", philo->id);
        philo->last_eat_time = ft_get_time1();
        usleep(philo->table->time_to_eat * 1000);
        philo->count_nbr_meals++;

        // Putting down forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Sleeping
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(philo->table->time_to_sleep * 1000);
    }
    return NULL;
}


// Helper function to get current time in milliseconds
uint64_t ft_get_time1(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Function to clean up and destroy resources
void cleanup(t_table *table) {
    for (int i = 0; i < table->nbr_philos; i++) {
        pthread_mutex_destroy(&table->forks[i]);
    }
    pthread_mutex_destroy(&table->table_mutex);
    free(table->forks);
    free(table->philos);
}

// Main function
int main(int argc, char **argv) {
    t_table table;

    // Validate arguments
    if (argc != 5 && argc != 6) {
        fprintf(stderr, "Usage: %s nbr_philos time_to_die time_to_eat time_to_sleep [nbr_meals]\n", argv[0]);
        return (1);
    }

    // Parse arguments
    table.nbr_philos = atoi(argv[1]);
    table.time_to_die = atoi(argv[2]);
    table.time_to_eat = atoi(argv[3]);
    table.time_to_sleep = atoi(argv[4]);
    table.nbr_meals = (argc == 6) ? atoi(argv[5]) : -1;

    if (table.nbr_philos <= 0 || table.time_to_die <= 0 || table.time_to_eat <= 0 || table.time_to_sleep <= 0) {
        fprintf(stderr, "Error: All arguments must be positive integers\n");
        return (1);
    }

    // Initialize table
    table.start_time = ft_get_time1();
    table.all_threads_created = false;
    table.end_time = false;
    table.forks = malloc(sizeof(pthread_mutex_t) * table.nbr_philos);
    table.philos = malloc(sizeof(t_philo) * table.nbr_philos);
    if (!table.forks || !table.philos) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return (1);
    }

    pthread_mutex_init(&table.table_mutex, NULL);
    for (int i = 0; i < table.nbr_philos; i++) {
        pthread_mutex_init(&table.forks[i], NULL);
    }

    // Initialize philosophers
    for (int i = 0; i < table.nbr_philos; i++) {
        table.philos[i].id = i + 1;
        table.philos[i].left_fork = &table.forks[i];
        table.philos[i].right_fork = &table.forks[(i + 1) % table.nbr_philos];
        table.philos[i].philo_full = false;
        table.philos[i].philo_died = false;
        table.philos[i].count_nbr_meals = 0;
        table.philos[i].last_eat_time = table.start_time;
        table.philos[i].table = &table;
    }

    //Create philosopher threads
    for (int i = 0; i < table.nbr_philos; i++) {
        if (pthread_create(&table.philos[i].thread_philo, NULL, philosopher_routine, &table.philos[i]) != 0) {
            fprintf(stderr, "Error: Failed to create thread\n");
            cleanup(&table);
            return (1);
        }
    }
    table.all_threads_created = true;

    // Monitor threads
    while (!table.end_time) {
        usleep(1000); // Check periodically (1 ms)
        // Add logic to detect if a philosopher has died or all meals are eaten
    }

    // Wait for threads to finish
    for (int i = 0; i < table.nbr_philos; i++) {
        pthread_join(table.philos[i].thread_philo, NULL);
    }

    // Cleanup
    cleanup(&table);
    return (0);
}