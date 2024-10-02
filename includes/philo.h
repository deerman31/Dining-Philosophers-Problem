/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:42:18 by ykusano           #+#    #+#             */
/*   Updated: 2023/07/14 19:18:06 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <stdatomic.h>

# define EAT_STR "is eating"
# define SLEEP_STR "is sleeping"
# define THINK_STR "is thinking"
# define DIE_STR "died"
# define FORK_STR "has taken a fork"

typedef enum e_act
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
}			t_act;

typedef struct s_philo
{
	int				philo_id;
	atomic_long		eat_cnt;
	atomic_long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*someone_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	long			philo_num;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			max_eat;

	atomic_int		stop;
	pthread_t		monitor;
	long			begin_time;

	t_philo			*top;
	size_t			size;
}			t_table;

int			check_arg(int argc, char **argv);
void		*routine(void *p);
void		*watchman(void *p);
//t_table		*table_set(char **argv);
int			table_set(char **argv, t_table *table);
long		now_time_set(long begin_time);
void		ft_sleep(long now, long begin, long act_time);
// bool		die_check(long now, long last_eat, long die_time);
// bool		print_log(t_philo *philo, t_table *table, t_act act);
// bool		philo_set(t_table *table);
int			die_check(long now, long last_eat, long die_time);
int			print_log(t_philo *philo, t_table *table, t_act act);
int			philo_set(t_table *table);

int			ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif
