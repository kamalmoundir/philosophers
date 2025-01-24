/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:29:25 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/24 16:29:33 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int	check_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (error_inputs("Error: wrong number of arguments\n"), 0);
	if (ft_atoi(av[i]) > 200)
		return (error_inputs("Error in the inputs"), 0);
	while (av[i])
	{
		if (!is_digit_nbr(av[i]) || ft_atoi(av[i]) < 1)
			return (error_inputs("Error in the inputs"), 0);
		i++;
	}
	if(ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		error_inputs("time stamp should be mas 60ms");
	return (1);
}

