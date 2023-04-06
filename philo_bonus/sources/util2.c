/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ph_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	len;

	len = strl(s1) + strl(s2) + 1;
	res = malloc(len);
	if (!res)
		return (0);
	ph_strlcpy(res, s1, len);
	ph_strlcat(res, s2, len);
	return (res);
}

int	ph_get_str_sign(const char *str)
{
	char	*trimmed;
	size_t	i;
	int		sign;

	if (!str)
		return (1);
	trimmed = ph_powertrim(str, "");
	if (!trimmed)
		return (1);
	i = 0;
	sign = 1;
	while (trimmed[i] && !ph_isdigit(trimmed[i]))
	{
		if (trimmed[i] == '-')
			sign *= -1;
		i ++;
	}
	free(trimmed);
	return (sign);
}

void	*ph_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*ptr;
	const char		*ptr2;

	if (dest == 0 && src == 0)
	{
		return (dest);
	}
	i = 0;
	ptr = dest;
	ptr2 = src;
	while (i < n)
	{
		*(ptr + i) = *(ptr2 + i);
		i ++;
	}
	return (dest);
}

long long	timenow(t_philo *philo)
{
	struct timeval	current_time;
	long long		res;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	res = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (philo == NULL)
		return (res);
	else
		return (res - philo->t0);
}
