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
	if (sem_wait(philo->right_to_take_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	//fprintf(stderr, "philo %d bruhhh1\n", philo->id);
	if (sem_wait(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	//fprintf(stderr, "philo %d bruhhh2\n", philo->id);
	log_fork(philo);
	//fprintf(stderr, "philo %d bruhhh3\n", philo->id);
	if (sem_wait(philo->fork_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	//fprintf(stderr, "philo %d bruhhh4\n", philo->id);
	if (sem_post(philo->right_to_take_sem) != 0)
	{
		panic_exit(philo, ERROR);
	}
	//fprintf(stderr, "philo %d bruhhh5\n", philo->id);
	log_fork(philo);
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
	//fprintf(stderr, "setting last eaten\n");
	//fprintf(stderr, "lasteaten: %p\n", (void*)&philo->mutex);
	sem_wait(philo->mainsem);
	philo->time_last_eaten = timenow(NULL);
	sem_post(philo->mainsem);
}
