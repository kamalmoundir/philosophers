/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:14:49 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 18:48:28 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_status(t_philo *philo,t_philo_status status)
{
    uint64_t start_sim;
    
    if(get_bool(&philo->table->print_status, &philo->table->end_time))
        return ;
    start_sim = philo->table->start_time;
    mutex_handl(&philo->table->print_status, LOCK);
    if(status == philo_eating)
        printf("%ld %d is eating\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == philo_sleeping)
        printf("%ld %d is sleeping\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == philo_thinking)
        printf("%ld %d is thinking\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == take_left_fork)
        printf("%ld %d has taken  a left fork\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == take_right_fork)
        printf("%ld %d has taken a right fork\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == philo_dead)
        printf("%ld %d died\n", ft_get_time() - start_sim, philo->id + 1);
    else if(status == philo_full)
        printf("%ld %d is full\n", ft_get_time() - start_sim, philo->id + 1);
    mutex_handl(&philo->table->print_status, UNLOCK);
}
