/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:29:25 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/26 21:18:17 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (error_inputs("Error: wrong number of arguments\n"), 0);
	if (ft_atoi(av[i]) > 200 || ft_atoi(av[i]) < 1)
		return (error_inputs("Error in the inputs"), 0);
	while (av[i])
	{
		if (!is_digit_nbr(av[i]) || ft_atoi(av[i]) < 0)
			return (error_inputs("Error in the inputs"), 0);
		i++;
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (error_inputs("time stamp should be mas 60ms"), 0);
	return (1);
}
