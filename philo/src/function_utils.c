/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:26:52 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 18:00:09 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(uint64_t time_sleep)
{
	uint64_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time_sleep)
	{
		usleep(100);
	}
}

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	*malloc_safe(size_t data_byte)
{
	size_t	result;

	result = malloc(data_byte);
	if (!result)
		return (NULL);
	return (result);
}

void	mutex_handl(pthread_mutex_t *mtx, t_orders order)
{
	if (order == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (order == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (order == LOCK)
		pthread_mutex_lock(mtx);
	else if (order == DESTROY)
		pthread_attr_destroy(mtx);
	else
		error_inputs("Error in mutex handling");
}

int	thread_handl(pthread_t thread, t_orders order, void *(*routine(void *)),
		void *data)
{
	if (order == CREATE)
	{
		if (pthread_create(thread, NULL, routine, data) != 0)
			return (error_inputs("Error: Failed to create thread\n"), 1);
	}
	else if (order == DETACH)
	{
		if (pthread_detach(thread))
			return (error_inputs("Error: Failed to detach thread\n"), 1);
	}
	else if (order == JOIN)
	{
		if (pthread_join(thread, NULL))
			return (error_inputs("Error: Failed to join thread\n"), 1);
	}
	return (0);
}

void	cleanup(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}

void *philo_routine(void *arg)
{
	
}