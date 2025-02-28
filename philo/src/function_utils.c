/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:26:52 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/28 13:49:10 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(uint64_t time_sleep , t_philo *philo)
{
	uint64_t	start;
	(void)philo;
	start = ft_get_time();
	while ((ft_get_time() - start) < time_sleep)
	{
		if (get_bool(&philo->table->table_mutex, &philo->table->end_time))
			return ;
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
	size_t	*result;

	result = malloc(data_byte);
	if (!result)
		return (NULL);
	return (result);
}

int	mutex_handl(pthread_mutex_t *mtx, t_orders order)
{
	if (mtx == NULL)
		return (error_inputs("Error: NULL mutex pointer"), -1);
	if (order == INIT)
	{
		if (pthread_mutex_init(mtx, NULL))
			return (error_inputs("Error: Failed to initialize mutex"), -1);
	}
	else if (order == LOCK)
	{
		if (pthread_mutex_lock(mtx))
			return (error_inputs("Error: Failed to lock mutex"), -1);
	}
	else if (order == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx))
			return (error_inputs("Error: Failed to unlock mutex"), -1);
	}
	else if (order == DESTROY)
	{
		if (pthread_mutex_destroy(mtx))
			return (error_inputs("Error: Failed to destroy mutex"), -1);
	}
	else
		return (error_inputs("Error: Invalid mutex handling order"), -1);
	return (0);
}

int	thread_handl(pthread_t *thread, t_orders order, void *(routine(void *)),
		void *data)
{
	if (order == CREATE)
	{
		if (pthread_create(thread, NULL, routine, data) != 0)
			return (error_inputs("Error: Failed to create thread\n"), 1);
	}
	else if (order == DETACH)
	{
		if (pthread_detach(*thread))
			return (error_inputs("Error: Failed to detach thread\n"), 1);
	}
	else if (order == JOIN)
	{
		if (pthread_join(*thread, NULL))
			return (error_inputs("Error: Failed to join thread\n"), 1);
	}
	return (0);
}
