/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchornization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:41:20 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 17:44:13 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void wait_to_be_ready(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->all_threads_created))
    ;
}