/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "stdlib.h"
# include "stdio.h"
# include "limits.h"
# include "pthread.h"
# include "unistd.h"

int		args_valid(int argc, char **argv);

typedef struct s_philo
{
	int	phil_num;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	num2eat;
}	t_philo;

void	init_struct(t_philo *philo, int argc, char *argv[]);

/* Util */
size_t	strl(const char *s);
int		ph_isdigit(int c);
int		ph_isspace(char c);
size_t	ph_strlcpy(char *dst, const char *src, size_t dstsize);
long	ph_atoi_l(const char *nptr);
void	*ph_memcpy(void *dest, const void *src, size_t n);
int		ph_get_str_sign(const char *str);
char	*ph_strjoin(char const *s1, char const *s2);
char	*ph_strtrim(char const *s1, char const *set);
char	*ph_powertrim(const char *str, const char *set);
size_t	ph_strlcat(char *dst, const char *src, size_t dstsize);
int		ph_str_is_int(const char *str);
int		ph_atoi(const char *nptr);

#endif
