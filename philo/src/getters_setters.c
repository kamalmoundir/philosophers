/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:10:24 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/24 21:27:26 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutx, bool *dest, bool value)
{
	mutex_handl(mutx, LOCK);
	*dest = value;
	mutex_handl(mutx, UNLOCK);
}
bool	get_bool(pthread_mutex_t *mutx, bool *dest)
{
	bool	value;

	mutex_handl(mutx, LOCK);
	value = *dest;
	mutex_handl(mutx, UNLOCK);
	return (value);
}

void	set_int(pthread_mutex_t *mutx, int *dest, int value)
{
	mutex_handl(mutx, LOCK);
	*dest = value;
	mutex_handl(mutx, UNLOCK);
}
int	get_int(pthread_mutex_t *mutx, int *dest)
{
	int	value;

	mutex_handl(mutx, LOCK);
	value = *dest;
	mutex_handl(mutx, UNLOCK);
	return (value);
}
void	set_time_val(pthread_mutex_t *mutx, uint64_t *dest, uint64_t value)
{
	mutex_handl(mutx, LOCK);
	*dest = value;
	mutex_handl(mutx, UNLOCK);
}
uint64_t	get_time_val(pthread_mutex_t *mutx, uint64_t dest)
{
	uint64_t value;

	mutex_handl(mutx, LOCK);
	value = dest;
	mutex_handl(mutx, UNLOCK);
	return (value);
}