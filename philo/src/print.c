/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:14:49 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/26 14:01:19 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_status(t_philo *philo,t_philo_status status)
{
    uint64_t start_sim;
    uint64_t timestamp;
    
    
    start_sim = philo->table->start_time;
    timestamp = ft_get_time()- start_sim;
    
   
   
  /*  if(get_bool(philo->table->print_status, &philo->table->end_time))
    {
        mutex_handl(philo->table->print_status, UNLOCK);
        return ;
    }*/
    mutex_handl(philo->table->print_status, LOCK);
    
    if(status == philo_eating)
        printf("%ld %d is eating\n", timestamp, philo->id);
    else if(status == philo_sleeping)
        printf("%ld %d is sleeping\n", timestamp, philo->id);
    else if(status == philo_thinking)
        printf("%ld %d is thinking\n", timestamp, philo->id);
    else if(status == take_left_fork)
        printf("%ld %d has taken  a left fork\n", timestamp, philo->id);
    else if(status == take_right_fork)
        printf("%ld %d has taken a right fork\n", timestamp, philo->id);
    else if(status == philo_dead)
        printf("%ld %d died\n", timestamp, philo->id + 1);
    else if(status == philo_full)
        printf("%ld %d is full\n", timestamp, philo->id);
    mutex_handl(philo->table->print_status, UNLOCK);
}
