/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:37:23 by sberete           #+#    #+#             */
/*   Updated: 2025/06/18 22:42:25 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		data->philo[i].data = data;
		data->philo[i].name = i + 1;
		data->philo[i].time_to_die = ft_atol(argv[2]);
		data->philo[i].time_to_eat = ft_atol(argv[3]);
		data->philo[i].time_to_sleep = ft_atol(argv[4]);
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meal_eaten = 0;
		data->philo[i].a = false;
		if (argc == 6)
			data->philo[i].must_eat = ft_atol(argv[5]);
		else
			data->philo[i].must_eat = -1;
		i++;
	}
}

bool	data_init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philosophers = ft_atol(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (false);
	data->pids = malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->pids)
	{
		free(data->philo);
		return (false);
	}
	data->start_time = actual_time();
	data->someone_died = 0;
	pthread_mutex_init(&data->death_mutex, NULL);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/died");
	sem_unlink("/philo_finished");
	data->fork = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philosophers);
	data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->died = sem_open("/died", O_CREAT | O_EXCL, 0644, 0);
	data->finished = sem_open("/philo_finished", O_CREAT | O_EXCL, 0644, 0);
	if (data->print_lock == SEM_FAILED || data->fork == SEM_FAILED
		|| data->died == SEM_FAILED || data->finished == SEM_FAILED)
		print_error(data, "sem_open failure");
	philo_init(data, argc, argv);
	return (true);
}
