/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_wrappers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	swait(sem_t *sem, t_philo *philo)
{
	int	res;

	res = sem_wait(sem);
	if (res != 0)
		panic_exit(philo, res);
}

void	spost(sem_t *sem, t_philo *philo)
{
	int	res;

	res = sem_post(sem);
	if (res != 0)
		panic_exit(philo, res);
}
