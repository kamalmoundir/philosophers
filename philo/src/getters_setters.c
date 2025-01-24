/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:10:24 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 17:02:31 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void set_bool(pthread_mutex_t *mutx, bool *dest, bool value)
{
    pthread_mutex_lock(mutx);
    *dest = value;
    pthread_mutex_unlock(mutx);
}
bool get_bool(pthread_mutex_t *mutx, bool *dest)
{
    bool value;

    pthread_mutex_lock(mutx);
    value = *dest;
    pthread_mutex_unlock(mutx);
    return (value);
}

void set_int(pthread_mutex_t *mutx, int *dest, int value)
{
    pthread_mutex_lock(mutx);
    *dest = value;
    pthread_mutex_unlock(mutx);
}
int get_int(pthread_mutex_t *mutx, int *dest)
{
    int value;

    pthread_mutex_lock(mutx);
    value = *dest;
    pthread_mutex_unlock(mutx);
    return (value);
}
void set_time_val(pthread_mutex_t *mutx, uint64_t *dest, uint64_t value)
{
    pthread_mutex_lock(mutx);
    *dest = value;
    pthread_mutex_unlock(mutx);
}
uint64_t get_time_val(pthread_mutex_t *mutx, uint64_t *dest)
{
    int value;

    pthread_mutex_lock(mutx);
    value = *dest;
    pthread_mutex_unlock(mutx);
    return (value);
}