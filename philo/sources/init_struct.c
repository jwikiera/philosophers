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

int	create_mutexes_and_threads(t_philo *philo)
{
	if (!create_forks(philo))
		return (0);
	philo->ts = NULL;
	philo->sophers = NULL;
	if (pthread_mutex_init(&(philo->sophers_mutex), NULL) != 0
		|| pthread_mutex_init(&(philo->death_mutex), NULL) != 0
		|| pthread_mutex_init(&(philo->done_eating_mutex), NULL) != 0
		|| pthread_mutex_init(&(philo->print_mutex), NULL) != 0)
		return (return_free_int(philo));
	philo->ts = alloc_ts(philo->phil_num);
	if (!philo->ts)
		return (return_free_int(philo));
	philo->sophers = init_sophers(philo->phil_num);
	if (!philo->sophers)
		return (return_free_int(philo));
	return (1);
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
	philo->spawning_done = 0;
	philo->spawn_count = 0;
	philo->spawn_count_copy = 0;
	philo->someone_died = 0;
	philo->mutexes = malloc(sizeof(pthread_mutex_t) * philo->phil_num);
	if (!philo->mutexes)
		return_free(philo);
	if (!create_mutexes_and_threads(philo))
		return (NULL);
	return (philo);
}

void	free_struct(t_philo *philo)
{
	int	i;

	if (philo->ts)
		free(philo->ts);
	i = 0;
	while (i < philo->phil_num)
	{
		pthread_mutex_destroy(&(philo->mutexes[i]));
		i ++;
	}
	pthread_mutex_destroy(&(philo->sophers_mutex));
	pthread_mutex_destroy(&(philo->death_mutex));
	pthread_mutex_destroy(&(philo->done_eating_mutex));
	pthread_mutex_destroy(&(philo->print_mutex));
	if (philo->sophers)
		free_sophers(philo->sophers, philo->phil_num);
	free(philo->mutexes);
	free(philo);
}
