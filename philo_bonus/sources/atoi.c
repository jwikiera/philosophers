/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	chr_to_dgt(char c)
{
	return (c - '0');
}

static int	whitespace_sign_limited(const char **nptr)
{
	while (ph_isspace(*(*nptr)))
		(*nptr)++;
	if (*(*nptr) == '-')
	{
		(*nptr)++;
		return (-1);
	}
	else if (*(*nptr) == '+')
	{
		(*nptr)++;
	}
	return (1);
}

int	ph_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = whitespace_sign_limited(&nptr);
	while (ph_isdigit(*nptr))
	{
		res = res * 10 + chr_to_dgt(*nptr);
		nptr ++;
	}
	return (res * sign);
}
