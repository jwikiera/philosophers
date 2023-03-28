/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep [number_of_times_each_philosopher_must_eat] */

void	*routine(void *arg_)
{
	t_arg *arg;
	t_philo	*philo;

	arg = arg_;
	philo = arg->philo;

	printf("lol from philo %d\n", arg->id + 1);
	while (!philo->someone_died)
	{
		if (!philo->sophers[arg->id]->is_eating && !philo->sophers[arg->id]->is_sleeping)
		{
			//fprintf(stderr, "%d bruh\n", arg->id);
			/*if (fork_status_left(philo, arg->id) == 0 && fork_status_right(philo, arg->id) == 0)
			{
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				//pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				philo->forks[get_index(philo, arg->id, 0)] = 1;
				log_fork_dir(arg->id, 0);

				if (fork_status_right(philo, arg->id) == 0)
				{
					pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
					philo->forks[get_index(philo, arg->id, 1)] = 1;
					log_fork_dir(arg->id, 1);
					log_eating(arg->id);
					philo->sophers[arg->id]->is_eating = 1;
					philo->sophers[arg->id]->time_when_started_eating = timenow();
					mysleep(philo->time2eat);
					philo->sophers[arg->id]->time_last_eaten = timenow();
					philo->forks[get_index(philo, arg->id, 0)] = 0;
					philo->forks[get_index(philo, arg->id, 1)] = 0;
					pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);
					pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				}
				else
				{
					fprintf(stderr, "right fork is blocked, removing lock on left from philosopher %d\n",
							arg->id);
					philo->forks[get_index(philo, arg->id, 0)] = 0;
					pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				}
			}*/
			if (arg->id != 0)
			{
				fprintf(stderr, "3bruhhh, %d\n", arg->id + 1);
				//taking left fork, happens second
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				philo->forks[get_index(philo, arg->id, 0)] = 1;
				log_fork_dir(arg->id, 0, get_index(philo, arg->id, 0));

				//taking right fork
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				philo->forks[get_index(philo, arg->id, 1)] = 1;
				log_fork_dir(arg->id, 1, -1);

				log_eating(arg->id);
				philo->sophers[arg->id]->is_eating = 1;
				philo->sophers[arg->id]->time_when_started_eating = timenow();
				mysleep(philo->time2eat);
				philo->sophers[arg->id]->time_last_eaten = timenow();
				philo->forks[get_index(philo, arg->id, 0)] = 0;
				philo->forks[get_index(philo, arg->id, 1)] = 0;
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);

			}
			else
			{
				//taking right fork, happens first
				fprintf(stderr, "2bruhhh, %d\n", arg->id + 1);
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				philo->forks[get_index(philo, arg->id, 1)] = 1;
				log_fork_dir(arg->id, 1, get_index(philo, arg->id, 1));

				//taking left fork
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				philo->forks[get_index(philo, arg->id, 0)] = 1;
				log_fork_dir(arg->id, 0, -3);

				log_eating(arg->id);
				philo->sophers[arg->id]->is_eating = 1;
				philo->sophers[arg->id]->time_when_started_eating = timenow();
				mysleep(philo->time2eat);
				philo->sophers[arg->id]->time_last_eaten = timenow();
				philo->forks[get_index(philo, arg->id, 1)] = 0;
				philo->forks[get_index(philo, arg->id, 0)] = 0;
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);


			}
		}
		if (philo->sophers[arg->id]->is_eating && (timenow() - philo->sophers[arg->id]->time_when_started_eating)
		>= philo->time2eat)
		{
			log_sleeping(arg->id);
			philo->sophers[arg->id]->is_eating = 0;
			philo->sophers[arg->id]->is_sleeping = 1;
			philo->sophers[arg->id]->time_when_started_sleeping = timenow();
			mysleep(philo->time2sleep);
		}
		if (philo->sophers[arg->id]->is_sleeping && (timenow() - philo->sophers[arg->id]->time_when_started_sleeping)
		>= philo->time2sleep)
		{
			philo->sophers[arg->id]->is_sleeping = 0;
			log_thinking(arg->id);
		}
	}
	free(arg);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_arg		*arg;

	if (!args_valid(argc, argv))
	{
		printf("Invalid arguments\n");
		return (0);
	}
	philo = init_struct(argc, argv);
	if (!philo)
		return (1);

	/*fprintf(stderr, "0, left: %d\n", get_index(philo, 0, 0));
	fprintf(stderr, "0, right: %d\n", get_index(philo, 0, 1));
	fprintf(stderr, "1, left: %d\n", get_index(philo, 1, 0));
	fprintf(stderr, "1, right: %d\n", get_index(philo, 1, 1));*/

	printf("starting with number of philos %d\n", philo->phil_num);
	arg = malloc(sizeof(arg) * philo->phil_num);
	if (!arg)
	{
		free(philo);
		return (2);
	}
	for (int i = 0; i < philo->phil_num; ++i) {
		arg[i].id = i;
		arg[i].philo = philo;
		pthread_create(&(philo->ts[i]), NULL, &routine, &arg[i]);
		//mysleep(500);
	}
	while (!philo->someone_died)
	{
		for (int i = 0; i < philo->phil_num; ++i) {
			if (!philo->someone_died && (timenow() - philo->sophers[i]->time_last_eaten) > philo->time2die)
			{
				log_ded(i);
				philo->someone_died = 1;
			}
		}
	}
	free_struct(philo);
	return (0);
}
