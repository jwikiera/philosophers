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

int	log_fork(t_philo *philo)
{
	swait(philo->write_sem, philo);
	printf("%lld %d has taken a fork\n", timenow(philo), philo->id);
	spost(philo->write_sem, philo);
	return (1);
}

int	log_eating(t_philo *philo)
{
	swait(philo->write_sem, philo);
	printf("%lld %d is eating\n", timenow(philo), philo->id);
	spost(philo->write_sem, philo);
	return (1);
}

int	log_sleeping(t_philo *philo)
{
	swait(philo->write_sem, philo);
	printf("%lld %d is sleeping\n", timenow(philo), philo->id);
	spost(philo->write_sem, philo);
	return (1);
}

int	log_thinking(t_philo *philo)
{
	swait(philo->write_sem, philo);
	printf("%lld %d is thinking\n", timenow(philo), philo->id);
	spost(philo->write_sem, philo);
	return (1);
}

int	log_ded(t_philo *philo)
{
	swait(philo->write_sem, philo);
	printf("%lld %d died\n", timenow(philo), philo->id);
	return (1);
}
