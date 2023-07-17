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
	//long	local_ttl;

	philo = arg_;
	/*local_ttl = philo->time_to_live;
	mysleepmicro(local_ttl);
	if (!philo->should_print)
		return (NULL);*/
	while (!get_philo_died(philo))
		mysleepmicro(10);
	die(philo);
	return (NULL);
}
