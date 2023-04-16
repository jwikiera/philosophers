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

void sig_handler_death(int signum)
{
	(void) signum;
	exit(DIED);
}

int	solo_routine(t_philo *philo)
{
	log_fork(philo);
	//mysleep(philo->time2die, philo);
	mysleepmicro(philo->time2die);
	log_ded(philo);
	free_struct(philo);
	return (0);
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
			fprintf(stderr, "hello from parent\n");
			philo->pids[i] = id;
		}
		else
		{
			fprintf(stderr, "hello from child, my id is %d\n", philo->id);
			routine(philo);
			break ;
		}
		i ++;
	}
	return (1);
}

void	main_loop(t_philo *philo)
{
	(void) philo;
	/*int	i;

	while (!get_someone_died(philo))
	{
		if (philo->num2eat > -1 && get_done_eating(philo) == philo->phil_num)
			set_dead(philo);
		else
		{
			i = 0;
			while (i < philo->phil_num)
			{
				if (!get_philo_died(philo) && (timenow(NULL)
						- get_time_last_eaten(philo, i)) > philo->time2die)
				{
					log_ded(philo, i);
					set_dead(philo);
				}
				i ++;
			}
		}
	}*/
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

int	main(int argc, char **argv)
{
	t_philo		*philo;
	int			i;
	int			wait_res;

	if (signal(SIGUSR1, sig_handler_death) == SIG_ERR)
		exit(ERROR);
	if (!args_valid(argc, argv))
		return (print_invalid_args());
	philo = init_struct(argc, argv);
	if (!philo)
	{
		fprintf(stderr, "bruh\n");
		return (1);
	}
	if (philo->phil_num < 1)
		return (0);
	philo->t0 = timenow(NULL);
	if (philo->phil_num == 1)
		return (solo_routine(philo));

	//todo: wait for any process to finish, read code, if it's death, kill all philos
	//otherwise wait for the rest, it means he ate enough

	create_and_wait_for_children(philo);
	i = 0;
	while (i < philo->phil_num)
	{
		if (wait(&wait_res) == -1)
		{
			killal_children(philo);
			panic_exit(philo, ERROR);
		}
		fprintf(stderr, "received wait: %d\n", wait_res);
		if (wait_res == DIED || wait_res == ERROR)
		{
			killal_children(philo);
			break ;
		}
		i ++;
	}
	//main_loop(philo);
	free_struct(philo);
	return (0);
}
