/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	log_fork(t_philo *philo, int id)
{
	if (get_someone_died(philo))
		return (1);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d has taken a fork\n", timenow(), id + 1);
	pthread_mutex_unlock(&philo->print_mutex);
	return (1);
}

int	log_fork_dir(int id, int dir, int fork_id)
{
	if (dir == 0)
		return (printf("%lld %d has taken left fork (%d)\n", timenow(), id + 1, fork_id) > 0);
	else
		return (printf("%lld %d has taken right fork (%d)\n", timenow(), id + 1, fork_id) > 0);
}

int	log_eating(t_philo *philo, int id)
{
	if (get_someone_died(philo))
		return (1);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d is eating\n", timenow(), id + 1);
	pthread_mutex_unlock(&philo->print_mutex);
	return (1);
}

int	log_sleeping(t_philo *philo, int id)
{
	if (get_done_eating(philo) == philo->phil_num)
		return (1);
	if (get_someone_died(philo))
		return (1);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d is sleeping\n", timenow(), id + 1);
	pthread_mutex_unlock(&philo->print_mutex);
	return (1);
}

int	log_thinking(t_philo *philo, int id)
{
	if (get_someone_died(philo))
		return (1);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d is thinking\n", timenow(), id + 1);
	pthread_mutex_unlock(&philo->print_mutex);
	return (1);
}

int	log_ded(t_philo *philo, int id)
{
	if (get_someone_died(philo))
		return (1);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d died\n", timenow(), id + 1);
	pthread_mutex_unlock(&philo->print_mutex);
	return (1);
}
