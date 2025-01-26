/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:50:38 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/26 12:44:03 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    
#include "../include/philo.h"

static	int	ft_isspace(int c)
{
	
	if (c == '\r' || c == '\f' || c == ' ' || c == '\n' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}
int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	i;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if(!nptr)
		return (0);
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
	{
		nbr *= 10;
		nbr += nptr[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int is_digit_nbr(char *av)
{
	int i;
	i=0;
	
	while(av[i])
	{
		if(av[i] < '0' || av[i] > '9')
		{
			return (0);
		}
			i ++;
	}
	return (1);
}