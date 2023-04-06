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

void	*routine(void *arg_)
{
	t_arg	*arg;
	t_philo	*philo;

	arg = arg_;
	philo = arg->philo;
	increase_spawn_count(philo);
	wait_for_spawns(arg->id, philo);
	pthread_mutex_lock(&philo->sophers_mutex);
	philo->sophers[arg->id]->time_last_eaten = timenow(NULL);
	pthread_mutex_unlock(&philo->sophers_mutex);
	if_odd_wait(arg->id, philo);
	while (!get_someone_died(philo))
	{
		grab_forks(arg->id, philo);
		set_lat_eaten(arg->id, philo);
		log_eating(philo, arg->id);
		mysleep(philo->time2eat, philo);
		increase_eat_counter(arg->id, philo);
		ungrab_forks(arg->id, philo);
		log_sleeping(philo, arg->id);
		mysleep(philo->time2sleep, philo);
		log_thinking(philo, arg->id);
	}
	return (NULL);
}
