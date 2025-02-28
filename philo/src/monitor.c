/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:24:30 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/28 13:10:06 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	uint64_t	elaps_time;
	uint64_t	last_meal;

	if (get_bool(&philo->philo_mutex, &philo->philo_full))
		return (false);
	
	last_meal = (uint64_t)get_time_val(&philo->philo_last_meal,
			philo->last_eat_time);
	elaps_time = (uint64_t)ft_get_time() - last_meal;
	if (elaps_time > get_time_val(&philo->table->table_mutex, philo->table->time_to_die))
	{
		if (get_bool(&philo->philo_mutex, &philo->is_eating))
			return (false);
		set_bool(&philo->philo_mutex, &philo->philo_died, true);
		print_status(philo, philo_dead);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (all_threads_runing(&table->table_mutex, &table->thread_runing_nbr,
			table->nbr_philos))
		;
	while (!simulation_end(table))
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (philo_died(&table->philos[i]) && !simulation_end(table))
			{
				set_bool(&table->table_mutex, &table->end_time, true);
				print_status(&table->philos[i], philo_dead);
				return (NULL);
			}
			i++;
		}
		if (check_all_philos_full(table))
			return (NULL);
	}
	return (NULL);
}

bool	check_all_philos_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (!get_bool(&table->table_mutex, &table->philos[i].philo_full))
			return (false);
		i++;
	}
	return (true);
}
