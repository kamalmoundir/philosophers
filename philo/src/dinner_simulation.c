/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:35:04 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/01 21:00:26 by kmoundir         ###   ########.fr       */
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
	{
		print_status(philo, philo_sleeping);
		ft_usleep(philo->table->time_to_sleep);
		thinking_routine(philo);
		return (NULL);
	}
	wait_to_be_ready(philo->table);
	increase_thread_nbr(&philo->table->table_mutex,
		&philo->table->thread_runing_nbr);
	desynchronize_philo(philo);
	if (get_bool(&philo->table->table_mutex, &philo->philo_full))
		return (NULL);
		
	while ((philo->table->nbr_meals > i || philo->table->nbr_meals == -1)
		&& !simulation_end(philo->table))
	{
		eat_routine(philo);
		print_status(philo, philo_sleeping);
		ft_usleep(philo->table->time_to_sleep);
		thinking_routine(philo);
		if (get_bool(&philo->table->table_mutex, &philo->philo_full))
			return (NULL);
		i++;
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	if (table->nbr_philos == 1)
	{
		print_status(&table->philos[0], take_left_fork);
		ft_usleep(table->time_to_die);
		print_status(&table->philos[0], philo_dead);
		mutex_handl(table->forks, UNLOCK);
		return ;
	}
	thread_handl(&table->monitor->monitor_thread, CREATE, monitor_routine,
		table);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (thread_handl(&table->philos[i].thread_philo, CREATE,
				philospher_routine, &table->philos[i]))
		{
			cleanup(table);
			return ;
		}
		i++;
	}
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_philo, NULL);
		i++;
	}
	pthread_join(table->monitor->monitor_thread, NULL);
	// set_bool(&table->table_mutex, &table->end_time, true);
}

void	eat_routine(t_philo *philo)
{
	uint64_t	tmp;

	mutex_handl(philo->left_fork, LOCK);
	print_status(philo, take_left_fork);
	mutex_handl(philo->right_fork, LOCK);
	print_status(philo, take_right_fork);
	set_time_val(&philo->table->table_mutex, &philo->last_eat_time,
		ft_get_time());
	print_status(philo, philo_eating);
	tmp = get_time_val(&philo->table->table_mutex, philo->table->time_to_eat);
	ft_usleep(tmp);
	if (philo->table->nbr_meals != -1)
	{
		philo->count_nbr_meals++;
		if (philo->count_nbr_meals == philo->table->nbr_meals)
		{
			set_bool(&philo->table->table_mutex, &philo->philo_full, true);
		}
	}
	mutex_handl(philo->left_fork, UNLOCK);
	mutex_handl(philo->right_fork, UNLOCK);
}

void	thinking_routine(t_philo *philo)
{
	if(philo->table->nbr_philos % 2 != 0)
	{
			ft_usleep(philo->table->time_to_eat / 4);
	}	
	print_status(philo, philo_thinking);
}

