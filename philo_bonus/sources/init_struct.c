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
	philo->someone_died = 0;
	philo->fork_sem = sem_open("/forks", O_CREAT, 0666, 1);
	philo->count_sem = sem_open("/count", O_CREAT, 0666, 1);
	if (philo->fork_sem == SEM_FAILED || philo->count_sem == SEM_FAILED)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	free_struct(t_philo *philo)
{
	if (philo->sophers)
		free_sophers(philo->sophers, philo->phil_num);
	free(philo);
}
