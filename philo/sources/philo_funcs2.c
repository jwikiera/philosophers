/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_eat_counter(int id, t_philo *philo)
{
	philo->sophers[id]->eat_count++;
	pthread_mutex_lock(&philo->done_eating_mutex);
	if (philo->sophers[id]->eat_count == philo->num2eat)
		philo->philos_done_eating++;
	pthread_mutex_unlock(&philo->done_eating_mutex);
}

void	ungrab_forks(int id, t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutexes[get_index(philo, id, 1)]);
	pthread_mutex_unlock(&philo->mutexes[get_index(philo, id, 0)]);
}
