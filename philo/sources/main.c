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


void	*routine(void *arg_)
{
	t_arg *arg;
	t_philo	*philo;

	arg = arg_;
	philo = arg->philo;

	printf("philo %d spawned\n", arg->id + 1);
	pthread_mutex_lock(&philo->sophers_mutex);
	philo->spawn_count++;
	pthread_mutex_unlock(&philo->sophers_mutex);

	//philo->sophers[arg->id]->time_last_eaten = -1;

	while (!philo->sophers[arg->id]->self_launched)
	{
		pthread_mutex_lock(&philo->death_mutex);
		philo->sophers[arg->id]->self_launched = philo->spawning_done;
		pthread_mutex_unlock(&philo->death_mutex);
		mysleep(10);
	}

	philo->sophers[arg->id]->time_last_eaten = timenow(NULL);
	if (arg->id % 2 != 0 &&!philo->sophers[arg->id]->fuse)
	{
		philo->sophers[arg->id]->fuse = 1;
		mysleep(200);
	}

	while (!get_someone_died(philo))
	{
		if (arg->id % 2 != 0)
		{
			//taking left fork
			pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
			log_fork(philo, arg->id);

			//taking right fork
			pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
			log_fork(philo, arg->id);
		}
		else
		{
			//taking right fork
			pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
			log_fork(philo, arg->id);

			//taking left fork
			pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
			log_fork(philo, arg->id);
		}

		//eat log
		log_eating(philo, arg->id);

		philo->sophers[arg->id]->time_when_started_eating = timenow(NULL);

		pthread_mutex_lock(&philo->sophers_mutex);
		philo->sophers[arg->id]->time_last_eaten = timenow(NULL);// + philo->time2eat;
		pthread_mutex_unlock(&philo->sophers_mutex);

		mysleep(philo->time2eat);

		//philo->sophers[arg->id]->eat_count++;
		//pthread_mutex_lock(&philo->done_eating_mutex);
		//if (philo->sophers[arg->id]->eat_count == philo->num2eat)
		//	philo->philos_done_eating++;
		//pthread_mutex_unlock(&philo->done_eating_mutex);

		//fprintf(stderr, "philo %d has eaten %d times now (max is %d)\n", arg->id + 1, philo->sophers[arg->id]->eat_count, philo->num2eat);

		pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);
		pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);

		pthread_mutex_lock(&philo->sophers_mutex);
		philo->sophers[arg->id]->time_last_eaten = timenow(NULL);
		pthread_mutex_unlock(&philo->sophers_mutex);

		log_sleeping(philo, arg->id);
		mysleep(philo->time2sleep);
		log_thinking(philo, arg->id);
	}
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
	if (philo->phil_num < 1)
		return (0);
	if (philo->phil_num == 1)
	{
		log_fork(philo, 0);
		mysleep(philo->time2die);
		log_ded(philo, 0);
		free_struct(philo);
		return (0);
	}
	arg = malloc(sizeof(*arg) * philo->phil_num);
	if (!arg)
	{
		free(philo);
		return (2);
	}

	pthread_mutex_lock(&philo->death_mutex);

	for (int i = 0; i < philo->phil_num; ++i) {
		arg[i].id = i;
		arg[i].philo = philo;
		pthread_create(&(philo->ts[i]), NULL, &routine, &arg[i]);
	}

	while (philo->spawn_count_copy < philo->phil_num)
	{
		pthread_mutex_lock(&philo->sophers_mutex);
		philo->spawn_count_copy = philo->spawn_count;
		pthread_mutex_unlock(&philo->sophers_mutex);
		mysleep(10);
	}

	philo->spawning_done = 1;
	philo->t0 = timenow(NULL);
	pthread_mutex_unlock(&philo->death_mutex);
	fprintf(stderr, "spawning done...\n");

	while (!get_someone_died(philo))
	{
		if (philo->num2eat > -1 && get_done_eating(philo) == philo->phil_num)
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->someone_died = 1;
			pthread_mutex_unlock(&philo->death_mutex);
		}
		else
		{
			for (int i = 0; i < philo->phil_num; ++i) {
				if (!get_someone_died(philo) && (timenow(NULL) - get_time_last_eaten(philo, i)) > philo->time2die)
				{
					log_ded(philo, i);
					pthread_mutex_lock(&philo->death_mutex);
					philo->someone_died = 1;
					pthread_mutex_unlock(&philo->death_mutex);
				}
			}
		}

	}
	for (int i = 0; i < philo->phil_num; ++i) {
		pthread_join((philo->ts[i]), NULL);
	}
	free(arg);
	free_struct(philo);
	return (0);
}
