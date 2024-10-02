#include "philo.h"

long	now_time_set(long begin_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - begin_time);
}

void	ft_sleep(long now, long begin, long act_time)
{
	long	time;

	if (act_time - 200 > 0)
		usleep(act_time - 200);
	time = now + act_time;
	while (now_time_set(begin) < time)
		usleep(100);
}

static int	eat_act(t_philo *philo, t_table *table)
{
	long		now;
	int			tf;

	pthread_mutex_lock(&philo->my_fork);
	print_log(philo, table, FORK);
	pthread_mutex_lock(philo->someone_fork);
	print_log(philo, table, FORK);
	now = now_time_set(table->begin_time);
	tf = print_log(philo, table, EATING);
	if (tf)
	{
		philo->last_eat = now;
		ft_sleep(now, table->begin_time, table->eat_time);
		philo->eat_cnt += 1;
	}
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(philo->someone_fork);
	return (tf);
}

static int	sleep_act(t_philo *philo, t_table *table)
{
	long	now;

	now = now_time_set(table->begin_time);
	if (!print_log(philo, table, SLEEPING))
		return (0);
	ft_sleep(now, table->begin_time, table->sleep_time);
	return (1);
}

void	*routine(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	if (philo->table->size == 1)
	{
		printf("%ld %d %s\n", now_time_set(philo->table->begin_time),
			1, FORK_STR);
		return (NULL);
	}
	if (philo->philo_id % 2 == 1)
		usleep(philo->table->eat_time * 1000 - 1);
	while (1)
	{
		if (!eat_act(philo, philo->table) || !sleep_act(philo, philo->table)
			|| !print_log(philo, philo->table, THINKING))
			break ;
	}
	return (NULL);
}
