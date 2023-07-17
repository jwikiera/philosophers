/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_sophers(t_sopher **sophers, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		free(sophers[i]);
		i ++;
	}
	free(sophers);
}

void	init_2(t_sopher	***res_, int i)
{
	t_sopher	**res;

	res = *res_;
	res[i]->time_last_eaten = timenow(NULL) + 100000;
	res[i]->time_when_started_eating = 0;
	res[i]->time_when_started_sleeping = 0;
	res[i]->is_eating = 0;
	res[i]->is_sleeping = 0;
	res[i]->eat_count = 0;
	res[i]->fuse = 0;
	res[i]->self_launched = 0;
}

t_sopher	**init_sophers(int amount)
{
	t_sopher	**res;
	int			i;

	res = malloc(sizeof(*res) * amount);
	if (!res)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		res[i] = malloc(sizeof(**res));
		if (!res[i])
		{
			free_sophers(res, i);
			return (NULL);
		}
		init_2(&res, i);
		i ++;
	}
	return (res);
}
