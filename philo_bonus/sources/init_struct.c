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
	philo->id = 1;
	philo->death_checker = NULL;
	philo->pids = NULL;
	if (argc == 6)
		philo->num2eat = ph_atoi(argv[5]);
	else
		philo->num2eat = -1;
	sem_unlink(FORKSEM);
	sem_unlink(RIGHTSEM);
	philo->fork_sem = sem_open(FORKSEM, O_CREAT, 0666, philo->phil_num);
	philo->fork_sem = sem_open(RIGHTSEM, O_CREAT, 0666, 1);
	if (philo->fork_sem == SEM_FAILED || philo->right_to_take_sem == SEM_FAILED)
	{
		sem_unlink(FORKSEM);
		sem_unlink(RIGHTSEM);
		free(philo);
		return (NULL);
	}
	philo->death_checker = malloc(sizeof(pthread_t));
	if (!philo->death_checker)
	{
		sem_unlink(FORKSEM);
		sem_unlink(RIGHTSEM);
		free(philo);
		return (NULL);
	}
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
	{
		sem_unlink(FORKSEM);
		sem_unlink(RIGHTSEM);
		free(philo->death_checker);
		free(philo);
		return (NULL);
	}
	philo->pids = malloc(sizeof(pid_t) * philo->phil_num);
	if (!philo->pids)
	{
		pthread_mutex_destroy(&philo->mutex);
		sem_unlink(FORKSEM);
		sem_unlink(RIGHTSEM);
		free(philo->death_checker);
		free(philo);
		return (NULL);
	}

	return (philo);
}

void	free_struct(t_philo *philo)
{
	if (philo->death_checker)
		free(philo->death_checker);
	sem_unlink(FORKSEM);
	sem_unlink(RIGHTSEM);
	pthread_mutex_destroy(&philo->mutex);
	if (philo->pids)
		free(philo->pids);
	free(philo);
}
