/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:35:42 by ykusano           #+#    #+#             */
/*   Updated: 2023/07/15 17:53:01 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	num_check(char *s)
{
	size_t	i;
	long	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		num = (num * 10) + (s[i] - '0');
		if (num > INT_MAX)
			return (0);
		i += 1;
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!num_check(argv[i]))
			return (0);
		i += 1;
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	return (1);
}
