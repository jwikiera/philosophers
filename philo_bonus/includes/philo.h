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
# include "sys/semaphore.h"
# include "fcntl.h"
# include "signal.h"
# include "string.h"
# include "errno.h"
# include "stdatomic.h"

# define FORKSEM "/forks"
# define RIGHTSEM "/righttotake"
# define DEATHSEM "/deathsem"
# define EATCOUNTSEM "/eatcountsem"
# define WRITESEM "/writesem"
# define WRITEACCESSSEM "/writeaccesssem"
# define MAINSEM "/mainsem"
# define FINISHEDEATING 1
# define DIED 2
# define ERROR 3

int			args_valid(int argc, char **argv);

typedef struct s_philo
{
	int				id;
	int				phil_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num2eat;
	long long		t0;
	sem_t			*fork_sem;
	sem_t			*right_to_take_sem;
	sem_t			*death_sem;
	sem_t			*eat_count_sem;
	sem_t			*write_sem;
	sem_t			*write_access_sem;
	int				can_write;
	_Atomic long	time_last_eaten;
	int				eat_count;
	pthread_t		*death_checker;
	sem_t			*mainsem;
	pid_t			*pids;
	_Atomic int		should_print;
	_Atomic long	time_to_live;
}	t_philo;

t_philo		*init_struct(int argc, char *argv[]);
void		free_struct(t_philo *philo);
void		routine(t_philo *philo);
void		panic_exit(t_philo *philo, int code);
void		*death_checker_routine(void *arg_);

/* logs */
int			log_fork(t_philo *philo);
int			log_eating(t_philo *philo);
int			log_sleeping(t_philo *philo);
int			log_thinking(t_philo *philo);
int			log_ded(t_philo *philo);
int			has_ability_to_write(t_philo *philo);
void		disable_ability_to_write(t_philo *philo);

/* philo funcs */
void		grab_forks(t_philo *philo);
void		ungrab_forks(t_philo *philo);
void		set_last_eaten(t_philo *philo);
int			solo_routine(t_philo *philo);
void		die(t_philo *philo);

/* main funcs */
int			print_invalid_args(void);
int			get_philo_died(t_philo *philo);

/* init */
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
char		*ph_itoa(int n);
long long	timenow(t_philo *philo);
void		mysleep(long long amount, t_philo *philo);
void		mysleepmicro(long long amount);
void		swait(sem_t *sem, t_philo *philo);
void		spost(sem_t *sem, t_philo *philo);

#endif
