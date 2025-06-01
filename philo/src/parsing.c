/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:23 by sberete           #+#    #+#             */
/*   Updated: 2025/06/01 20:17:31 by sxrimu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parsing(t_data data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (false);
	if (data.number_of_philosophers > 200)
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
static void philo_init(t_data *data, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		pthread_mutex_init(&data->philo[i].meal_eaten_lock, NULL);
		data->philo[i].data = data;
		data->philo[i].name = i + 1;
		data->philo[i].time_to_die = ft_atol(argv[2]);
		data->philo[i].time_to_eat = ft_atol(argv[3]);
		data->philo[i].time_to_sleep = ft_atol(argv[4]);
		if (argc == 6)
			data->philo[i].must_eat = ft_atol(argv[5]);
		else
			data->philo[i].must_eat = -1;
		i++;
	}
}

bool	init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philosophers = ft_atol(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (false);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->someone_died_lock, NULL);
	data->start_time = actual_time();
	philo_init(data, argc, argv);
	return (true);
}
