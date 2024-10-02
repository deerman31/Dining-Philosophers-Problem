#include "philo.h"

static long	begin_time_set(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	fork_set(t_table *table)
{
	size_t		i;
	t_philo		*philo;

	i = 0;
	philo = table->top;
	while (i < table->size)
	{
		philo->someone_fork = &philo->next->my_fork;
		philo = philo->next;
		i += 1;
	}
}

int	table_set(char **argv, t_table *table)
{
	table->philo_num = ft_atoi(argv[1]);
	table->die_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = INT_MAX;
	table->top = NULL;
	table->size = 0;
	table->begin_time = begin_time_set();
	table->stop = ATOMIC_VAR_INIT(0);
	if (!philo_set(table))
		return (0);
	fork_set(table);
	return (1);
}
