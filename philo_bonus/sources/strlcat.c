/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:00:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 12:00:28 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	my_min(size_t a, size_t b)
{
	if (b < a)
	{
		return (b);
	}
	return (a);
}

size_t	my_strnlen(const char *s, size_t maxlen)
{
	return (my_min(strl(s), maxlen));
}

size_t	ph_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = strl(src);
	dstlen = my_strnlen(dst, dstsize);
	if (dstlen == dstsize)
		return (dstsize + srclen);
	if (srclen < dstsize - dstlen)
		ph_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ph_memcpy(dst + dstlen, src, dstsize - dstlen - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dstlen + srclen);
}
