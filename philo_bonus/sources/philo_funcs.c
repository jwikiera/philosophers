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
	philo->should_print = 1;
	if (sem_wait(philo->right_to_take_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	if (sem_wait(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	log_fork(philo);
	if (sem_wait(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	if (sem_post(philo->right_to_take_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	log_fork(philo);
	philo->should_print = 0;
}

void	ungrab_forks(t_philo *philo)
{
	if (sem_post(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	if (sem_post(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
}

void	set_last_eaten(t_philo *philo)
{
	philo->time_last_eaten = timenow(NULL);
}

void	die(t_philo *philo)
{
	int	i;

	spost(philo->death_sem, philo);
	log_ded(philo);
	i = 0;
	while (i < philo->phil_num * philo->num2eat)
		spost(philo->eat_count_sem, philo);
}
