/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_t	*alloc_ts(int num)
{
	pthread_t	*res;

	res = malloc(sizeof(pthread_t) * num);
	if (!res)
		return (NULL);
	return (res);
}

t_philo	*init_struct(int argc, char *argv[])
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (NULL);
	philo->phil_num = ph_atoi(argv[1]);
	philo->time2die = ph_atoi(argv[2]);
	philo->time2eat = ph_atoi(argv[3]);
	philo->time2sleep = ph_atoi(argv[4]);
	if (argc == 6)
		philo->num2eat = ph_atoi(argv[5]);
	else
		philo->num2eat = -1;
	philo->forks = malloc(sizeof(*(philo->forks)) * philo->phil_num);
	if (!philo->forks)
	{
		free(philo);
		return (NULL);
	}
	philo->mutexes = malloc(sizeof(pthread_mutex_t) * philo->phil_num);
	if (!philo->mutexes)
	{
		free(philo->forks);
		free(philo);
		return (NULL);
	}
	for (int i = 0; i < philo->phil_num; ++i) {
		if (pthread_mutex_init(&(philo->mutexes[i]), NULL) != 0)
		{
			free(philo->forks);
			free(philo->mutexes);
			free(philo);
			return (NULL);
		}
	}
	philo->ts = alloc_ts(philo->phil_num);
	if (!philo->ts)
	{
		free(philo->forks);
		free(philo->mutexes);
		free(philo);
		return (NULL);
	}
	philo->sophers = init_sophers(philo->phil_num);
	if (!philo->sophers)
	{
		free(philo->forks);
		free(philo->mutexes);
		free(philo->ts);
		free(philo);
		return (NULL);
	}
	philo->someone_died = 0;
	return (philo);
}

void	free_struct(t_philo *philo)
{
	free(philo->forks);
	free(philo->ts);
	for (int i = 0; i < philo->phil_num; ++i) {
		pthread_mutex_destroy(&(philo->mutexes[i]));
	}
	free_sophers(philo->sophers, philo->phil_num);
	free(philo);
}
