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

	//printf("lol from philo %d\n", arg->id + 1);

	while (!get_someone_died(philo) && (!(philo->num2eat > -1) || (philo->num2eat > -1 && philo->sophers[arg->id]->eat_count < philo->num2eat)))
	{
		if (!philo->sophers[arg->id]->is_eating && !philo->sophers[arg->id]->is_sleeping)
		{
			if (arg->id % 2 != 0)
			{
				//taking left fork, happens second
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				log_fork(philo, arg->id);

				//taking right fork
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				log_fork(philo, arg->id);

				log_eating(philo, arg->id);

				philo->sophers[arg->id]->is_eating = 1;
				philo->sophers[arg->id]->time_when_started_eating = timenow();

				pthread_mutex_lock(&philo->sophers_mutex);
				philo->sophers[arg->id]->time_last_eaten = timenow() + philo->time2eat;
				pthread_mutex_unlock(&philo->sophers_mutex);

				mysleep(philo->time2eat);
				philo->sophers[arg->id]->eat_count++;
				pthread_mutex_lock(&philo->done_eating_mutex);
				if (philo->sophers[arg->id]->eat_count == philo->num2eat)
					philo->philos_done_eating++;
				pthread_mutex_unlock(&philo->done_eating_mutex);
				//fprintf(stderr, "philo %d has eaten %d times now (max is %d)\n", arg->id, philo->sophers[arg->id]->eat_count, philo->num2eat);

				pthread_mutex_lock(&philo->sophers_mutex);
				philo->sophers[arg->id]->time_last_eaten = timenow();
				pthread_mutex_unlock(&philo->sophers_mutex);

				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);

			}
			else
			{
				//taking right fork, happens first
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 1)]);
				log_fork(philo, arg->id);

				//taking left fork
				pthread_mutex_lock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				log_fork(philo, arg->id);

				log_eating(philo, arg->id);

				philo->sophers[arg->id]->is_eating = 1;
				philo->sophers[arg->id]->time_when_started_eating = timenow();

				pthread_mutex_lock(&philo->sophers_mutex);
				philo->sophers[arg->id]->time_last_eaten = timenow() + philo->time2eat;
				pthread_mutex_unlock(&philo->sophers_mutex);

				mysleep(philo->time2eat);
				philo->sophers[arg->id]->eat_count++;
				pthread_mutex_lock(&philo->done_eating_mutex);
				if (philo->sophers[arg->id]->eat_count == philo->num2eat)
					philo->philos_done_eating++;
				pthread_mutex_unlock(&philo->done_eating_mutex);
				//fprintf(stderr, "philo %d has eaten %d times now (max is %d)\n", arg->id, philo->sophers[arg->id]->eat_count, philo->num2eat);

				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 0)]);
				pthread_mutex_unlock(&philo->mutexes[get_index(philo, arg->id, 1)]);


			}
		}
		if (philo->sophers[arg->id]->is_eating && (timenow() - philo->sophers[arg->id]->time_when_started_eating)
		>= philo->time2eat)
		{
			log_sleeping(philo, arg->id);
			philo->sophers[arg->id]->is_eating = 0;
			philo->sophers[arg->id]->is_sleeping = 1;
			philo->sophers[arg->id]->time_when_started_sleeping = timenow();
			mysleep(philo->time2sleep);
		}
		if (philo->sophers[arg->id]->is_sleeping && (timenow() - philo->sophers[arg->id]->time_when_started_sleeping)
		>= philo->time2sleep)
		{
			philo->sophers[arg->id]->is_sleeping = 0;
			log_thinking(philo, arg->id);
		}
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
	for (int i = 0; i < philo->phil_num; ++i) {
		arg[i].id = i;
		arg[i].philo = philo;
		pthread_create(&(philo->ts[i]), NULL, &routine, &arg[i]);
	}

	while (!get_someone_died(philo) && (!(philo->num2eat > -1) || (philo->num2eat > -1 && get_done_eating(philo) < philo->phil_num)))
	{
		for (int i = 0; i < philo->phil_num; ++i) {
			if (!get_someone_died(philo) && (timenow() - get_time_last_eaten(philo, i)) > philo->time2die)
			{
				log_ded(philo, i);
				pthread_mutex_lock(&philo->death_mutex);
				philo->someone_died = 1;
				pthread_mutex_unlock(&philo->death_mutex);
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
