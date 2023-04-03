/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	strl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[0])
	{
		s ++;
		i ++;
	}
	return (i);
}

int	ph_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ph_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f');
}

size_t	ph_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (strl(src));
	i = 0;
	while (i < dstsize - 1 && i < strl(src))
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = 0;
	return (strl(src));
}

char	*ph_powertrim(const char *str, const char *set)
{
	char	*joined_set;
	char	*res;

	joined_set = ph_strjoin(set, " \f\n\r\t\v");
	if (!joined_set)
		return (NULL);
	res = ph_strtrim(str, joined_set);
	free(joined_set);
	return (res);
}
