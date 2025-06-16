/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:37:23 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 19:49:42 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].data = data;
		data->philo[i].name = i + 1;
		data->philo[i].time_to_die = ft_atol(argv[2]);
		data->philo[i].time_to_eat = ft_atol(argv[3]);
		data->philo[i].time_to_sleep = ft_atol(argv[4]);
		data->philo[i].last_meal = data->start_time;
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
		return (false);
	data->start_time = actual_time();
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/philo_finished");
	data->fork = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philosophers);
	if (data->fork == SEM_FAILED)
	{
		printf("sem_open fork");
		exit(EXIT_FAILURE);
	}
	data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_lock == SEM_FAILED)
	{
		printf("sem_open print_lock");
		exit(EXIT_FAILURE);
	}
	philo_init(data, argc, argv);
	return (true);
}
