/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:53:16 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 20:03:01 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time_val(pthread_mutex_t *mutx, uint64_t *dest, uint64_t value)
{
	mutex_handl(mutx, LOCK);
	*dest = value;
	mutex_handl(mutx, UNLOCK);
}

uint64_t	get_time_val(pthread_mutex_t *mutx, uint64_t dest)
{
	uint64_t	value;

	mutex_handl(mutx, LOCK);
	value = dest;
	mutex_handl(mutx, UNLOCK);
	return (value);
}
