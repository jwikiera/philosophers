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

long	get_ttl(t_philo *philo)
{
	return (philo->time2die - (timenow(NULL) - philo->time_last_eaten));
}

void	create_thread(t_philo *philo)
{
	if (pthread_create(philo->death_checker,
			NULL, &death_checker_routine, philo))
		panic_exit(philo, ERROR);
}

void	routine(t_philo *philo)
{
	set_last_eaten(philo);
	if (philo->id % 2)
		mysleep(20, philo);
	create_thread(philo);
	while (!get_philo_died(philo))
	{
		philo->time_to_live = get_ttl(philo);

		grab_forks(philo);
		//pthread_detach(*philo->death_checker);
		set_last_eaten(philo);
		log_eating(philo);
		mysleep(philo->time2eat, philo);
		if (get_philo_died(philo))
			die(philo);
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
	die(philo);
}
