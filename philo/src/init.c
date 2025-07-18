/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:37:23 by sberete           #+#    #+#             */
/*   Updated: 2025/07/18 19:10:26 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->philo[i].mutex.right_fork, NULL);
		pthread_mutex_init(&data->philo[i].mutex.meal_eaten_lock, NULL);
		pthread_mutex_init(&data->philo[i].mutex.last_meal_lock, NULL);
		data->philo[i].data = data;
		data->philo[i].name = i + 1;
		data->philo[i].time.to_die = ft_atol(argv[2]);
		data->philo[i].time.to_eat = ft_atol(argv[3]);
		data->philo[i].time.to_sleep = ft_atol(argv[4]);
		data->philo[i].last_meal = data->start_time;
		if (argc == 6)
			data->philo[i].time.must_eat = ft_atol(argv[5]);
		else
			data->philo[i].time.must_eat = -1;
		i++;
	}
}

bool	data_init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philo = ft_atol(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (false);
	pthread_mutex_init(&data->mutex.print_lock, NULL);
	pthread_mutex_init(&data->mutex.someone_died_lock, NULL);
	pthread_mutex_init(&data->mutex.finish_lock, NULL);
	data->start_time = actual_time();
	philo_init(data, argc, argv);
	if (data->number_of_philo > 200 || data->philo->time.to_die < 60
		|| data->philo->time.to_sleep < 60 || data->philo->time.to_eat < 60)
	{
		cleanup_philosophers(data);
		return (false);
	}
	return (true);
}
