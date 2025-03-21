/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:10:24 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 19:59:28 by kmoundir         ###   ########.fr       */
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
