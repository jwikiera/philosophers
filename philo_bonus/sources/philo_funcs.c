/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo)
{
	swait(philo->fork_sem, philo);
	log_fork(philo);
	swait(philo->fork_sem, philo);
	log_fork(philo);
}

void	ungrab_forks(t_philo *philo)
{
	spost(philo->fork_sem, philo);
	spost(philo->fork_sem, philo);
}

void	set_last_eaten(t_philo *philo)
{
	philo->time_last_eaten = timenow(NULL);
}
