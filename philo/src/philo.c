/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:12:56 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/24 21:41:38 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table table;

	if (check_input(ac, av) == 0)
		return (1);
	init_table(&table, av);
	init_philo(&table);
	start_dinner(&table);
	cleanup(&table);
	return (0);
}