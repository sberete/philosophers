/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:23 by sberete           #+#    #+#             */
/*   Updated: 2025/05/16 16:51:24 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parsing(t_data data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (false);
	i = 1;
	if (data.number_of_philosophers > 200)
		return (false);
	while (argv[i])
	{
		if (valid_number(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

t_data	init(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.number_of_philosophers = ft_atol(argv[1]);
	data.ap = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	if (!data.ap)
		exit(0);
	data.philo.time_to_die = ft_atol(argv[2]);
	data.philo.time_to_eat = ft_atol(argv[3]);
	data.philo.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data.philo.must_eat = ft_atol(argv[5]);
	return (data);
}
