/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	log_fork(int id)
{
	return (printf("%lld %d has taken a fork\n", timenow(), id) > 0);
}

int	log_eating(int id)
{
	return (printf("%lld %d is eating\n", timenow(), id) > 0);
}

int	log_sleeping(int id)
{
	return (printf("%lld %d is sleeping\n", timenow(), id) > 0);
}

int	log_thinking(int id)
{
	return (printf("%lld %d is thinking\n", timenow(), id) > 0);
}

int	log_ded(int id)
{
	return (printf("%lld %d died\n", timenow(), id) > 0);
}
