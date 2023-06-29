/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	post_eat_sems(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num * philo->num2eat)
	{
		sem_post(philo->eat_count_sem);
		i ++;
	}
}

void	routine(t_philo *philo)
{
	philo->time_last_eaten = timenow(NULL);
	while (!get_philo_died(philo))
	{
		grab_forks(philo);
		philo->time_last_eaten = timenow(NULL);
		log_eating(philo);
		mysleep(philo->time2eat, philo);
		if (philo->eat_count < philo->num2eat)
		{
			philo->eat_count++;
			sem_post(philo->eat_count_sem);
		}
		ungrab_forks(philo);
		log_sleeping(philo);
		mysleep(philo->time2sleep, philo);
		log_thinking(philo);
	}
	log_ded(philo);
	spost(philo->death_sem, philo);
	post_eat_sems(philo);
}
