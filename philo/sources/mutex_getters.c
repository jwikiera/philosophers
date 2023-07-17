/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_done_eating(t_philo *philo)
{
	int	philos_done_eating_copy;

	pthread_mutex_lock(&philo->done_eating_mutex);
	philos_done_eating_copy = philo->philos_done_eating;
	pthread_mutex_unlock(&philo->done_eating_mutex);
	return (philos_done_eating_copy);
}

int	get_someone_died(t_philo *philo)
{
	int	someone_died_copy;

	pthread_mutex_lock(&philo->death_mutex);
	someone_died_copy = philo->someone_died;
	pthread_mutex_unlock(&philo->death_mutex);
	return (someone_died_copy);
}

long	get_time_last_eaten(t_philo *philo, int id)
{
	long	time_last_eaten_copy;

	pthread_mutex_lock(&philo->sophers_mutex);
	time_last_eaten_copy = philo->sophers[id]->time_last_eaten;
	pthread_mutex_unlock(&philo->sophers_mutex);
	return (time_last_eaten_copy);
}
