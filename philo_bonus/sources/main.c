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

int	solo_routine(t_philo *philo)
{
	log_fork(philo, 0);
	mysleep(philo->time2die, philo);
	log_ded(philo, 0);
	free_struct(philo);
	return (0);
}

void	create_and_wait_for_threads(t_philo *philo, t_arg *arg)
{
	int	i;

	pthread_mutex_lock(&philo->death_mutex);
	i = 0;
	while (i < philo->phil_num)
	{
		arg[i].id = i;
		arg[i].philo = philo;
		pthread_create(&(philo->ts[i]), NULL, &routine, &arg[i]);
		i ++;
	}
	while (philo->spawn_count_copy < philo->phil_num)
	{
		pthread_mutex_lock(&philo->sophers_mutex);
		philo->spawn_count_copy = philo->spawn_count;
		pthread_mutex_unlock(&philo->sophers_mutex);
		usleep(10);
	}
	philo->spawning_done = 1;
	philo->t0 = timenow(NULL);
	pthread_mutex_unlock(&philo->death_mutex);
}

void	main_loop(t_philo *philo)
{
	int	i;

	while (!get_someone_died(philo))
	{
		if (philo->num2eat > -1 && get_done_eating(philo) == philo->phil_num)
			set_dead(philo);
		else
		{
			i = 0;
			while (i < philo->phil_num)
			{
				if (!get_someone_died(philo) && (timenow(NULL)
						- get_time_last_eaten(philo, i)) > philo->time2die)
				{
					log_ded(philo, i);
					set_dead(philo);
				}
				i ++;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_arg		*arg;

	if (!args_valid(argc, argv))
		return (print_invalid_args());
	philo = init_struct(argc, argv);
	if (!philo)
		return (1);
	if (philo->phil_num < 1)
		return (0);
	if (philo->phil_num == 1)
		return (solo_routine(philo));
	arg = malloc(sizeof(*arg) * philo->phil_num);
	if (!arg)
	{
		free(philo);
		return (2);
	}
	create_and_wait_for_threads(philo, arg);
	main_loop(philo);
	join_threads(philo);
	return (free_everything(philo, arg));
}
