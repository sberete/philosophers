/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:04:28 by sberete           #+#    #+#             */
/*   Updated: 2025/07/18 19:24:07 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	sem_wait(data->sem.died);
	while (i < data->number_of_philosophers)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}

void	*finish_monitor(void *arg)
{
	t_monitor_info	*info;
	t_data			*data;
	int				i;

	info = (t_monitor_info *)arg;
	data = info->data;
	i = 0;
	while (i < info->finished_required)
	{
		sem_wait(data->sem.finished);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}

void	parent_process(t_data *data)
{
	pthread_t		death_thread;
	pthread_t		finish_thread;
	t_monitor_info	info;
	int				i;

	info.data = data;
	info.finished_required = data->number_of_philosophers;
	pthread_create(&death_thread, NULL, death_monitor, data);
	if (data->philo->time.must_eat != -1)
		pthread_create(&finish_thread, NULL, finish_monitor, &info);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
	cleanup_philosophers(data);
}
