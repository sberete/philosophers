/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:37:23 by sberete           #+#    #+#             */
/*   Updated: 2025/07/19 12:38:57 by sxrimu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	sema_init(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/died");
	sem_unlink("/philo_finished");
	sem_unlink("/active");
	data->sem.fork = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philosophers);
	data->sem.print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->sem.died = sem_open("/died", O_CREAT | O_EXCL, 0644, 0);
	data->sem.finished = sem_open("/philo_finished", O_CREAT | O_EXCL, 0644, 0);
	data->sem.active = sem_open("/active", O_CREAT | O_EXCL, 0644, data->number_of_philosophers - 1);
	if (data->sem.print_lock == SEM_FAILED || data->sem.fork == SEM_FAILED
		|| data->sem.died == SEM_FAILED || data->sem.finished == SEM_FAILED || data->sem.active == SEM_FAILED)
	{
		cleanup_philosophers(data);
		return (1);
	}
	return (0);
}

static void	philo_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		data->philo[i].data = data;
		data->philo[i].name = i + 1;
		data->philo[i].time.to_die = ft_atol(argv[2]);
		data->philo[i].time.to_eat = ft_atol(argv[3]);
		data->philo[i].time.to_sleep = ft_atol(argv[4]);
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meal_eaten = 0;
		data->philo[i].a = false;
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
	data->number_of_philosophers = ft_atol(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (false);
	data->pids = malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->pids)
		return (false);
	data->start_time = actual_time();
	if (sema_init(data) == 1)
		return (false);
	philo_init(data, argc, argv);
	if (data->number_of_philosophers > 200 || data->philo->time.to_die < 60
		|| data->philo->time.to_sleep < 60 || data->philo->time.to_eat < 60)
	{
		cleanup_philosophers(data);
		return (false);
	}
	return (true);
}
