/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:35:04 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/28 14:11:31 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philospher_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->table->nbr_meals == 0)
		return (case_no_meals(philo), NULL);
	wait_to_be_ready(philo->table);
	increase_thread_nbr(&philo->table->table_mutex,
		&philo->table->thread_runing_nbr);
	desynchronize_philo(philo);
	if (get_bool(&philo->table->table_mutex, &philo->philo_full))
		return (NULL);
	if(simulation_end(philo->table)) return (NULL);
	while ((philo->table->nbr_meals > i || philo->table->nbr_meals == -1)
		&& !simulation_end(philo->table))
	{
		eat_routine(philo);
		print_status(philo, philo_sleeping);
		ft_usleep(get_time_val(&philo->table->table_mutex,philo->table->time_to_sleep),philo);
		thinking_routine(philo);
		if (get_bool(&philo->table->table_mutex, &philo->philo_full))
			return (NULL);
		i++;
	}
	return (NULL);
}

void	*start_dinner(t_table *table)
{
	int	i;

	if (table->nbr_philos == 1)
		return (only_philo(table), NULL);
	thread_handl(&table->monitor->monitor_thread, CREATE, monitor_routine,
		table);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (thread_handl(&table->philos[i].thread_philo, CREATE,
				philospher_routine, &table->philos[i]))
			return (cleanup(table), NULL);
		i++;
	}
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].thread_philo, NULL);
	pthread_join(table->monitor->monitor_thread, NULL);
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	uint64_t	tmp;
	
	if (philo->id % 2 == 0)
	{
		mutex_handl(philo->right_fork, LOCK);
		print_status(philo, take_right_fork);
		mutex_handl(philo->left_fork, LOCK);
		print_status(philo, take_left_fork);
	}
	else
	{
		mutex_handl(philo->left_fork, LOCK);
		print_status(philo, take_left_fork);
		mutex_handl(philo->right_fork, LOCK);
		print_status(philo, take_right_fork);
	}
	print_status(philo, philo_eating);
	
	set_bool(&philo->philo_mutex, &philo->is_eating, true);
	
	mutex_handl(&philo->philo_mutex, LOCK);
	set_time_val(&philo->philo_last_meal, &philo->last_eat_time,
		ft_get_time());
		mutex_handl(&philo->philo_mutex, UNLOCK);
		
		
	tmp = get_time_val(&philo->table->table_mutex, philo->table->time_to_eat);
	ft_usleep(tmp,philo);
	if (philo->table->nbr_meals != -1)
	{
		philo->count_nbr_meals++;
		if (philo->count_nbr_meals == philo->table->nbr_meals)
		{
			set_bool(&philo->table->table_mutex, &philo->philo_full, true);
		}
	}
	set_bool(&philo->philo_mutex, &philo->is_eating, false);
	mutex_handl(philo->right_fork, UNLOCK);
	mutex_handl(philo->left_fork, UNLOCK);
}

void	thinking_routine(t_philo *philo)
{
	print_status(philo, philo_thinking);	
}
