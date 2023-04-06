/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_num_digits(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = strl(str);
	while (i < len)
	{
		if (!ph_isdigit(str[i]) && !ph_isspace(str[i])
			&& str[i] != '-' && str[i] != '+')
			return (0);
		i ++;
	}
	return (1);
}

static char	*inttrim(const char *str)
{
	char	*trimmed;
	char	*res;
	int		i;

	trimmed = ph_powertrim(str, "+-");
	if (strl(trimmed) == 1 && trimmed[0] == '0')
		return (trimmed);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (trimmed[i] && trimmed[i] == '0')
		i ++;
	res = malloc(strl(trimmed) - i + 1);
	if (!res)
	{
		free(trimmed);
		return (NULL);
	}
	ph_strlcpy(res, trimmed + i, strl(trimmed) - i + 1);
	free(trimmed);
	return (res);
}

static int	has_only_digits(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = strl(str);
	while (i < len)
	{
		if (!ph_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

static int	free_trimmed(char *str)
{
	if (str)
		free(str);
	return (0);
}

int	ph_str_is_int(const char *str)
{
	char	*trimmed;
	int		sign;

	if (!str || !has_num_digits(str))
		return (0);
	sign = ph_get_str_sign(str);
	trimmed = inttrim(str);
	if (!trimmed || strl(trimmed) == 0)
		return (free_trimmed(trimmed));
	if (!has_only_digits(trimmed))
		return (free_trimmed(trimmed));
	if (strl(trimmed) > 10)
		return (free_trimmed(trimmed));
	if (ph_atoi_l(trimmed) * sign > INT_MAX
		|| ph_atoi_l(trimmed) * sign < INT_MIN)
		return (free_trimmed(trimmed));
	free(trimmed);
	return (1);
}
