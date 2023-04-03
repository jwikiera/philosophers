/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mallocs threads */
pthread_t	*alloc_ts(int num)
{
	pthread_t	*res;

	res = malloc(sizeof(pthread_t) * num);
	if (!res)
		return (NULL);
	return (res);
}

int	create_forks(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_mutex_init(&(philo->mutexes[i]), NULL) != 0)
		{
			j = 0;
			while (j < i - 1)
			{
				pthread_mutex_destroy(&(philo->mutexes[j]));
				j ++;
			}
			free(philo->mutexes);
			free(philo);
			return (0);
		}
		i ++;
	}
	return (1);
}

t_philo	*return_free(t_philo *philo)
{
	free(philo);
	return (NULL);
}

int	return_free_int(t_philo *philo)
{
	free_struct(philo);
	return (0);
}
