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

	printf("lol from philo %d\n", arg->id);
	/*while (!philo->someone_died)
	{

	}*/
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
	printf("starting with number of philos %d\n", philo->phil_num);
	for (int i = 0; i < philo->phil_num; ++i) {
		arg = malloc(sizeof(*arg));
		if (!arg)
		{
			free(philo);
			return (2);
		}
		arg->id = i;
		arg->philo = philo;
		pthread_create(&(philo->ts[i]), NULL, &routine, arg);
	}
	free_struct(philo);
	return (0);
}
