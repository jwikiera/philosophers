/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker_routine(void *arg_)
{
	t_philo	*philo;
	int		i;

	philo = arg_;
	set_last_eaten(philo);
	while (!get_philo_died(philo))
	{
		mysleepmicro(10);
	}
	log_ded(philo);
	sem_post(philo->death_sem);
	i = 0;
	while (i < philo->phil_num * philo->num2eat)
		sem_post(philo->eat_count_sem);
	return (NULL);
}
