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

void	init_one(t_philo *philo, char *argv[], int argc)
{
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
	philo->can_write = 1;
	sem_unlink(FORKSEM);
	sem_unlink(RIGHTSEM);
	sem_unlink(DEATHSEM);
	sem_unlink(EATCOUNTSEM);
	sem_unlink(WRITESEM);
	sem_unlink(WRITEACCESSSEM);
	sem_unlink(MAINSEM);
	philo->fork_sem = sem_open(FORKSEM, O_CREAT, 0666, philo->phil_num);
	philo->right_to_take_sem = sem_open(RIGHTSEM, O_CREAT, 0666, 1);
	philo->death_sem = sem_open(DEATHSEM, O_CREAT, 0666, 0);
	philo->eat_count_sem = sem_open(EATCOUNTSEM, O_CREAT, 0666, 0);
	philo->write_sem = sem_open(WRITESEM, O_CREAT, 0666, 1);
	philo->write_access_sem = sem_open(WRITEACCESSSEM, O_CREAT, 0666, 1);
}

t_philo	*ret_unlink(t_philo *philo, int free_deathchecker)
{
	sem_unlink(FORKSEM);
	sem_unlink(RIGHTSEM);
	sem_unlink(DEATHSEM);
	sem_unlink(EATCOUNTSEM);
	if (free_deathchecker)
		free(philo->death_checker);
	free(philo);
	return (NULL);
}

t_philo	*init_struct(int argc, char *argv[])
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (NULL);
	init_one(philo, argv, argc);
	philo->mainsem = sem_open(MAINSEM, O_CREAT, 0666, 1);
	if (philo->fork_sem == SEM_FAILED || philo->right_to_take_sem == SEM_FAILED
		|| philo->death_sem == SEM_FAILED || philo->eat_count_sem == SEM_FAILED
		|| philo->write_sem == SEM_FAILED
		|| philo->write_access_sem == SEM_FAILED
		|| philo->mainsem == SEM_FAILED)
		return (ret_unlink(philo, 0));
	philo->death_checker = malloc(sizeof(pthread_t));
	if (!philo->death_checker)
		return (ret_unlink(philo, 0));
	philo->pids = malloc(sizeof(pid_t) * philo->phil_num);
	if (!philo->pids)
		return (ret_unlink(philo, 1));
	philo->can_write = 1;
	return (philo);
}

void	free_struct(t_philo *philo)
{
	if (philo->death_checker)
		free(philo->death_checker);
	sem_unlink(FORKSEM);
	sem_unlink(RIGHTSEM);
	sem_unlink(DEATHSEM);
	sem_unlink(EATCOUNTSEM);
	if (philo->pids)
		free(philo->pids);
	free(philo);
}
