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
	pthread_create(philo->death_checker, NULL, &death_checker_routine, philo);
	philo->time_last_eaten = timenow(NULL);
	while (!get_philo_died(philo))
	{
		grab_forks(philo);
		set_lat_eaten(philo);
		log_eating(philo);
		mysleep(philo->time2eat, philo);
		philo->eat_count++;
		if (philo->eat_count == philo->num2eat)
			panic_exit(philo, FINISHEDEATING);
		ungrab_forks(philo);
		log_sleeping(philo);
		mysleep(philo->time2sleep, philo);
		log_thinking(philo);
	}
}
