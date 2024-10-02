/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:36:28 by ykusano           #+#    #+#             */
/*   Updated: 2023/07/15 17:36:29 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die_check(long now, long last_eat, long die_time)
{
	if (now - last_eat <= die_time)
		return (0);
	return (1);
}

int	print_log(t_philo *philo, t_table *table, t_act act)
{
	long	now;

	if (table->stop == 1)
		return (0);
	now = now_time_set(table->begin_time);
	if (die_check(now, philo->last_eat, table->die_time))
	{
		table->stop = 1;
		printf("%ld %d %s\n", now, philo->philo_id, DIE_STR);
		return (0);
	}
	if (act == FORK)
		printf("%ld %d %s\n", now, philo->philo_id, FORK_STR);
	else if (act == EATING)
		printf("%ld %d %s\n", now, philo->philo_id, EAT_STR);
	else if (act == SLEEPING)
		printf("%ld %d %s\n", now, philo->philo_id, SLEEP_STR);
	else if (act == THINKING)
		printf("%ld %d %s\n", now, philo->philo_id, THINK_STR);
	return (1);
}
