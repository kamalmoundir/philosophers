/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:29:17 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 19:43:31 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->nbr_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->nbr_meals = ft_atoi(av[5]);
	else
		table->nbr_meals = -1;
	table->forks = malloc_safe((table->nbr_philos) * sizeof(pthread_mutex_t));
	table->print_status = malloc_safe(sizeof(pthread_mutex_t));
	table->philos = malloc_safe((table->nbr_philos) * sizeof(t_philo));
	table->monitor = malloc_safe(sizeof(t_monitor));
	table->start_time = ft_get_time();
	table->all_threads_created = false;
	table->end_time = false;
	table->thread_runing_nbr = 0;
	mutex_handl(&table->table_mutex, INIT);
	mutex_handl(table->print_status, INIT);
	mutex_handl(&table->monitor->monitor_mutex, INIT);
	while (i < table->nbr_philos)
		mutex_handl(&table->forks[i++], INIT);
}

void	assign_forks(t_table *table, int pos)
{
	if (table->philos[pos].id == 1)
	{
		table->philos[pos].left_fork = &table->forks[pos];
		table->philos[pos].right_fork = &table->forks[(pos + 1)
			% table->nbr_philos];
	}
	else if (table->philos[pos].id % 2 == 0)
	{
		table->philos[pos].right_fork = &table->forks[(pos + 1)
			% table->nbr_philos];
		table->philos[pos].left_fork = &table->forks[pos];
	}
	else
	{
		table->philos[pos].right_fork = &table->forks[pos];
		table->philos[pos].left_fork = &table->forks[(pos + 1)
			% table->nbr_philos];
	}
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].philo_died = false;
		table->philos[i].philo_full = false;
		table->philos[i].count_nbr_meals = 0;
		table->philos[i].last_eat_time = table->start_time;
		table->philos[i].table = table;
		mutex_handl(&table->philos[i].philo_mutex, INIT);
		assign_forks(table, i);
		i++;
	}
}
