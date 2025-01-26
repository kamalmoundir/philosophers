/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:12:56 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/26 13:29:43 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"



int	main(int ac, char **av)
{
    t_table *table;
    (void)ac;
	//if (check_input(ac, av) == 0)
		//return (1);
    table = malloc_safe(sizeof(t_table));
    init_table(table , av);
    init_philo(table);
    start_dinner(table);
    cleanup(table);

	return (0);
}