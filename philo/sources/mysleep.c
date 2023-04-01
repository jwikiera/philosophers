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

/* sleep in microseconds */
void	mysleepmicro(long long amount)
{
	long long	wake_time;

	wake_time = timenow(NULL) + amount;
	while (timenow(NULL) < wake_time)
		usleep(100);
}

/* sleep in milliseconds, interrupt if someone dies */
void	mysleep(long long amount, t_philo *philo)
{
	long long	wake_time;

	wake_time = timenow(NULL) + amount;
	while (timenow(NULL) < wake_time)
	{
		if (get_someone_died(philo))
			break ;
		usleep(100);
	}
}
