/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:36:14 by ykusano           #+#    #+#             */
/*   Updated: 2023/07/15 22:07:51 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*philo_create(t_table *table, int id)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->philo_id = id;
	philo->eat_cnt = ATOMIC_VAR_INIT(0);
	philo->last_eat = ATOMIC_VAR_INIT(0);
	pthread_mutex_init(&philo->my_fork, NULL);
	philo->next = philo;
	philo->prev = philo;
	philo->table = table;
	return (philo);
}

static void	sit_down(t_table *table, t_philo *philo)
{
	t_philo		*last;

	if (table->top == NULL)
		table->top = philo;
	else
	{
		last = table->top->prev;
		last->next = philo;
		philo->prev = last;
		table->top->prev = philo;
		philo->next = table->top;
	}
	table->size += 1;
}

static void	philo_free(t_table *table)
{
	size_t		i;
	t_philo		*free_n;

	i = 0;
	while (i < table->size)
	{
		free_n = table->top;
		table->top = table->top->next;
		pthread_mutex_destroy(&free_n->my_fork);
		free(free_n);
		i += 1;
	}
}

int	philo_set(t_table *table)
{
	size_t		i;
	t_philo		*philo;

	i = 0;
	while (i < (size_t)table->philo_num)
	{
		philo = philo_create(table, (int)(i + 1));
		if (philo == NULL)
		{
			philo_free(table);
			return (0);
		}
		sit_down(table, philo);
		i += 1;
	}
	return (1);
}
