/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchornization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:41:20 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 19:44:54 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_to_be_ready(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_created))
		;
}

bool	all_threads_runing(pthread_mutex_t *mutx, int *thread_r, int philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handl(mutx, LOCK);
	if (*thread_r == philo_nbr)
		ret = true;
	mutex_handl(mutx, UNLOCK);
	return (ret);
}

void	increase_thread_nbr(pthread_mutex_t *mutx, int *val)
{
	mutex_handl(mutx, LOCK);
	(*val)++;
	mutex_handl(mutx, UNLOCK);
}

void	desynchronize_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 4);
}

bool	simulation_end(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_time));
}
