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

#ifndef PHILO_H
# define PHILO_H

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
	int		eat_count;
	int		fuse;
	int		self_launched;
}	t_sopher;

typedef struct s_philo
{
	int				phil_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num2eat;
	pthread_mutex_t	*mutexes;
	int				someone_died;
	pthread_t		*ts;
	t_sopher		**sophers;
	int				philos_done_eating;
	pthread_mutex_t	sophers_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	done_eating_mutex;
	pthread_mutex_t	print_mutex;
	int				spawning_done;
	long long		t0;
	int				spawn_count;
	int				spawn_count_copy;
}	t_philo;

typedef struct s_arg
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
void		*routine(void *arg_);

/* logs */
int			log_fork(t_philo *philo, int id);
int			log_eating(t_philo *philo, int id);
int			log_sleeping(t_philo *philo, int id);
int			log_thinking(t_philo *philo, int id);
int			log_ded(t_philo *philo, int id);

/* mutex getters */
int			get_done_eating(t_philo *philo);
int			get_someone_died(t_philo *philo);
long		get_time_last_eaten(t_philo *philo, int id);

/* philo funcs */
void		increase_spawn_count(t_philo *philo);
void		wait_for_spawns(int id, t_philo *philo);
void		if_odd_wait(int id, t_philo *philo);
void		grab_forks(int id, t_philo *philo);
void		ungrab_forks(int id, t_philo *philo);
void		set_lat_eaten(int id, t_philo *philo);
void		increase_eat_counter(int id, t_philo *philo);

/* main funcs */
void		set_dead(t_philo *philo);
void		join_threads(t_philo *philo);
int			free_everything(t_philo *philo, t_arg *arg);
int			print_invalid_args(void);

/* init */
pthread_t	*alloc_ts(int num);
int			create_forks(t_philo *philo);
t_philo		*return_free(t_philo *philo);
int			return_free_int(t_philo *philo);

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
long long	timenow(t_philo *philo);
void		mysleep(long long amount, t_philo *philo);
void		mysleepmicro(long long amount);

#endif
