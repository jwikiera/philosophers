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

int	print_invalid_args(void)
{
	printf("Invalid arguments\n");
	return (0);
}

int	get_philo_died(t_philo *philo)
{
	int	ret;

	sem_wait(philo->mainsem);
	ret = timenow(NULL) - philo->time_last_eaten > philo->time2die;
	sem_post(philo->mainsem);
	return (ret);
}
