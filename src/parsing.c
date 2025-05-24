/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:23 by sberete           #+#    #+#             */
/*   Updated: 2025/05/24 19:38:11 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parsing(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (false);
	i = 1;
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
	int		i;

	memset(&data, 0, sizeof(t_data));
	data.number_of_philosophers = ft_atol(argv[1]);
	data.philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!data.philo)
		exit(0);
	data.philo->time_to_die = ft_atol(argv[2]);
	data.philo->time_to_eat = ft_atol(argv[3]);
	data.philo->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data.philo->must_eat = ft_atol(argv[5]);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_init(&data.philo[i].right_fork, NULL);
		data.philo[i].name = i + 1;
		i++;
	}
	return (data);
}
