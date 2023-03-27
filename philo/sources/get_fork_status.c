/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* returns the index to the given side of a philosopher */
/* 0 is left, 1 is right */
int	get_index(t_philo *philo, int id, int direction)
{
	int	res;

	if (direction == 0)
		res = ((id - 1) % philo->phil_num);
	else
		res = ((id + 1) % philo->phil_num);
	if (res == -1)
		res = philo->phil_num - 1;
	return (res);
}

/* returns 1 if a fork is taken, 0 if available */
int	fork_status_left(t_philo *philo, int id)
{
	int	res;

	pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 0)]);
	res = philo->forks[get_index(philo, id, 0)];
	pthread_mutex_unlock(&philo->mutexes[get_index(philo, id, 0)]);
	return (res);
}

/* returns 1 if a fork is taken, 0 if available */
int	fork_status_right(t_philo *philo, int id)
{
	int	res;

	pthread_mutex_lock(&philo->mutexes[get_index(philo, id, 0)]);
	res = philo->forks[get_index(philo, id, 1)];
	pthread_mutex_unlock(&philo->mutexes[get_index(philo, id, 0)]);
	return (res);
}
