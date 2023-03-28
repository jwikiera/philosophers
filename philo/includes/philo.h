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
# include "sys/time.h"

int			args_valid(int argc, char **argv);

typedef struct s_sopher
{
	long	time_last_eaten;
	long	time_when_started_sleeping;
	long	time_when_started_eating;
	int		is_eating;
	int		is_sleeping;
}	t_sopher;

typedef struct s_philo
{
	int				phil_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num2eat;
	int				*forks;
	pthread_mutex_t	*mutexes;
	int				someone_died;
	pthread_t		*ts;
	t_sopher		**sophers;
}	t_philo;

typedef struct	s_arg
{
	int		id;
	t_philo	*philo;
}	t_arg;

t_philo		*init_struct(int argc, char *argv[]);
void		free_struct(t_philo *philo);
t_sopher	**init_sophers(int amount);
void		free_sophers(t_sopher **sophers, int amount);
int			fork_status_left(t_philo *philo, int id);
int			fork_status_right(t_philo *philo, int id);
int			get_index(t_philo *philo, int id, int direction);

/* logs */
int			log_fork(int id);
int			log_eating(int id);
int			log_sleeping(int id);
int			log_thinking(int id);
int			log_ded(int id);
int			log_fork_dir(int id, int dir, int fork_id);

/* Util */
size_t		strl(const char *s);
int			ph_isdigit(int c);
int			ph_isspace(char c);
size_t		ph_strlcpy(char *dst, const char *src, size_t dstsize);
long		ph_atoi_l(const char *nptr);
void		*ph_memcpy(void *dest, const void *src, size_t n);
int			ph_get_str_sign(const char *str);
char		*ph_strjoin(char const *s1, char const *s2);
char		*ph_strtrim(char const *s1, char const *set);
char		*ph_powertrim(const char *str, const char *set);
size_t		ph_strlcat(char *dst, const char *src, size_t dstsize);
int			ph_str_is_int(const char *str);
int			ph_atoi(const char *nptr);
long long	timenow();
void		mysleep(long long amount);

#endif
