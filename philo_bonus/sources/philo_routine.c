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

void	routine(t_philo *philo)
{
	//fprintf(stderr, "hello from routine of philo %d!\n", philo->id);
	pthread_create(philo->death_checker, NULL, &death_checker_routine, philo);
	//fprintf(stderr, "philo %d, created thread\n", philo->id);
	set_last_eaten(philo);
	while (!get_philo_died(philo))
	{
		//fprintf(stderr, "philo %d, dupa 1\n", philo->id);
		grab_forks(philo);
		//fprintf(stderr, "philo %d, dupa 2\n", philo->id);
		set_last_eaten(philo);
		log_eating(philo);
		mysleep(philo->time2eat, philo);
		if (philo->eat_count < philo->num2eat)
		{
			philo->eat_count++;
			sem_post(philo->eat_count_sem);
		}
			//panic_exit(philo, FINISHEDEATING);

		ungrab_forks(philo);
		log_sleeping(philo);
		mysleep(philo->time2sleep, philo);
		log_thinking(philo);
	}
}
