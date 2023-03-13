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
 * time_to_sleep[number_of_times_each_philosopher_must_eat] */

int	main(int argc, char **argv)
{
	if (!args_valid(argc, argv))
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (0);
}
