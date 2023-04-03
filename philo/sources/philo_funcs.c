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

void	increase_spawn_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->sophers_mutex);
	philo->spawn_count++;
	pthread_mutex_unlock(&philo->sophers_mutex);
}

void	wait_for_spawns(int id, t_philo *philo)
{
	while (!philo->sophers[id]->self_launched)
	{
		pthread_mutex_lock(&philo->death_mutex);
		philo->sophers[id]->self_launched = philo->spawning_done;
		pthread_mutex_unlock(&philo->death_mutex);
		usleep(100);
	}
}

void	if_odd_wait(int id, t_philo *philo)
{
	if (id % 2 != 0 &&!philo->sophers[id]->fuse)
	{
		philo->sophers[id]->fuse = 1;
		usleep(10);
	}
}

void	grab_forks(int id, t_philo *philo)
{
	if (id % 2 != 0)
	{
		pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 0)]);
		log_fork(philo, id);
		pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 1)]);
		log_fork(philo, id);
	}
	else
	{
		pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 1)]);
		log_fork(philo, id);
		pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 0)]);
		log_fork(philo, id);
	}
}

void	set_lat_eaten(int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->sophers_mutex);
	philo->sophers[id]->time_last_eaten = timenow(NULL);
	pthread_mutex_unlock(&philo->sophers_mutex);
}
