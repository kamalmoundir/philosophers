/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_simulaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:35:04 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 19:19:53 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philospher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (get_bool(&philo->table->table_mutex, &philo->philo_full))
		return (NULL);
	wait_to_be_ready(philo->table);
    //last_eat_time

    while(philo->table->end_time == false)
    {
    //eat 
    eat_routine(philo);
    //sleep
    print_status(philo, philo_sleeping);
    ft_usleep(philo->table->time_to_sleep);

    //think
    thinking_routine(philo);
    }
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_meals == 0)
	{
		table->end_time = true;
		return ;
	}
	if (table->nbr_philos == 1)
	{
		printf("0 %d has taken a fork\n", 1);
		printf("0 %d is eating\n", 1);
		printf("0 %d is sleeping\n", 1);
		printf("0 %d is thinking\n", 1);
		return ;
	}
	while (i < table->nbr_philos)
	{
		if (thread_handl(&table->philos[i].thread_philo, CREATE, philo_routine,
				&table->philos[i]))
		{
			cleanup(table);
			return ;
		}
		i++;
	}
	table->start_time = ft_get_time();
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_philo, NULL);
		i++;
	}
}

void eat_routine(t_philo *philo)
{
    mutex_handl(philo->left_fork, LOCK);
    print_status(philo, take_left_fork);
    mutex_handl(philo->right_fork, LOCK);
    print_status(philo, take_right_fork);
    
    set_time_val(&philo->table->table_mutex, &philo->last_eat_time, ft_get_time());
    print_status(philo, philo_eating);
    ft_usleep(philo->table->time_to_eat);
    if(philo->table->nbr_meals != -1)
    {
       philo->count_nbr_meals++;
        if(philo->count_nbr_meals == philo->table->nbr_meals)
            set_bool(&philo->table->table_mutex, &philo->philo_full, true);
    }
    mutex_handl(philo->left_fork, UNLOCK);
    mutex_handl(philo->right_fork, UNLOCK);
}

void thinking_routine(t_philo *philo)
{
    print_status(philo, philo_thinking);
}
