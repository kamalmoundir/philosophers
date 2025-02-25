/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:06:28 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 20:24:04 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	case_no_meals(t_philo *philo)
{
	print_status(philo, philo_sleeping);
	ft_usleep(philo->table->time_to_sleep);
	thinking_routine(philo);
}

void	only_philo(t_table *table)
{
	print_status(&table->philos[0], take_left_fork);
	ft_usleep(table->time_to_die);
	print_status(&table->philos[0], philo_dead);
	mutex_handl(table->forks, UNLOCK);
}
