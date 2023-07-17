/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_ability_to_write(t_philo *philo)
{
	int	res;

	swait(philo->write_access_sem, philo);
	res = philo->can_write;
	sem_post(philo->write_access_sem);
	return (res);
}

void	disable_ability_to_write(t_philo *philo)
{
	swait(philo->write_access_sem, philo);
	philo->can_write = 1;
	sem_post(philo->write_access_sem);
}
