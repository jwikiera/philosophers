/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sig_handler_death(int signum)
{
	(void) signum;
	fprintf(stderr, "received sigusr1\n");
	exit(DIED);
}

int	create_and_wait_for_children(t_philo *philo)
{
	int		i;
	pid_t	id;

	i = 0;
	while (i < philo->phil_num)
	{
		id = fork();
		if (id < 0)
			panic_exit(philo, ERROR);
		if (id != 0)
		{
			philo->id++;
			philo->pids[i] = id;
		}
		else
		{
			routine(philo);
			break ;
		}
		i ++;
	}
	return (1);
}

void	killal_children(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num)
	{
		kill(philo->pids[i], SIGKILL);
		i ++;
	}
}

void	wait_for_philos_to_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num * philo->num2eat)
	{
		sem_wait(philo->eat_count_sem);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	if (signal(SIGUSR1, sig_handler_death) == SIG_ERR)
		exit(ERROR);
	if (!args_valid(argc, argv))
		return (print_invalid_args());
	philo = init_struct(argc, argv);
	if (!philo)
		return (1);
	if (philo->phil_num < 1)
		return (0);
	philo->t0 = timenow(NULL);
	if (philo->phil_num == 1)
		return (solo_routine(philo));
	create_and_wait_for_children(philo);
	if (philo->num2eat == -1)
		sem_wait(philo->death_sem);
	else
		wait_for_philos_to_eat(philo);
	killal_children(philo);
	free_struct(philo);
	return (0);
}
