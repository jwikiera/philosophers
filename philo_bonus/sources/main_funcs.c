/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	philo->someone_died = 1;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num)
	{
		pthread_join((philo->ts[i]), NULL);
		i ++;
	}
}

int	print_invalid_args(void)
{
	printf("Invalid arguments\n");
	return (0);
}
