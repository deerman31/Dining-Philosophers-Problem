#include "philo.h"

static void	routine_start(t_table *table)
{
	size_t		i;
	t_philo		*philo;

	i = 0;
	philo = table->top;
	while (i < (size_t)table->philo_num)
	{
		pthread_create(&philo->thread, NULL, routine, philo);
		philo = philo->next;
		i += 1;
	}
	pthread_create(&table->monitor, NULL, watchman, table);
}

static void	philo_free(t_table *table)
{
	size_t		i;
	t_philo		*philo;
	t_philo		*free_p;

	i = 0;
	philo = table->top;
	while (i < table->size)
	{
		free_p = philo;
		philo = philo->next;
		pthread_mutex_destroy(&free_p->my_fork);
		free(free_p);
		i += 1;
	}
}

static void	program_close(t_table *table)
{
	size_t		i;
	t_philo		*philo;

	i = 0;
	philo = table->top;
	while (i < table->size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i += 1;
	}
	pthread_join(table->monitor, NULL);
	philo_free(table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_arg(argc, argv))
	{
		printf("Error: bad argument\n");
		return (1);
	}
	if (!table_set(argv, &table))
	{
		printf("Error: init error\n");
		return (1);
	}
	routine_start(&table);
	program_close(&table);
	return (0);
}
