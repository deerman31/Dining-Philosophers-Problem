#include "philo.h"

static int	confirm_survive(t_philo *philo, t_table *table)
{
	long		time;

	time = now_time_set(table->begin_time);
	if (table->stop)
		return (1);
	else if (die_check(time, philo->last_eat, table->die_time))
	{
		table->stop = 1;
		printf("%ld %d %s\n", time, philo->philo_id, DIE_STR);
		return (1);
	}
	return (0);
}

void	*watchman(void *p)
{
	t_table	*table;
	t_philo	*philo;
	long	i;

	table = (t_table *)p;
	philo = table->top;
	i = 0;
	while (i != -1)
	{
		if (philo == table->top)
			i = 0;
		if (confirm_survive(philo, table))
			i = -1;
		if (philo->eat_cnt >= table->max_eat)
			i += 1;
		if (philo == table->top->prev && i == table->philo_num)
			i = -1;
		philo = philo->next;
	}
	table->stop = 1;
	return (NULL);
}
