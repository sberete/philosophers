/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:04:28 by sberete           #+#    #+#             */
/*   Updated: 2025/07/17 20:42:38 by sxrimu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*void	parent_process(t_data *data)
{
	int	i;

	if (data->number_of_philosophers == 1)
		sem_wait(data->sem.died);
	else if (data->philo->time.must_eat != -1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			sem_wait(data->sem.finished);
			i++;
		}
	}
	else
		sem_wait(data->sem.died);
	i = 0;
	while (i < data->number_of_philosophers)
		kill(data->pids[i++], SIGKILL);
	i = 0;
	while (i < data->number_of_philosophers)
		waitpid(data->pids[i++], NULL, 0);
	cleanup_philosophers(data);
}*/
void	*death_monitor(void *arg)
{
	t_data	*data = (t_data *)arg;

	sem_wait(data->sem.died);
	// Un philosophe est mort
	for (int i = 0; i < data->number_of_philosophers; i++)
		kill(data->pids[i], SIGKILL);
	return (NULL);
}

void	*finish_monitor(void *arg)
{
	t_monitor_info	*info = (t_monitor_info *)arg;
	t_data			*data = info->data;

	for (int i = 0; i < info->finished_required; i++)
		sem_wait(data->sem.finished);

	// Tous ont terminé de manger
	for (int i = 0; i < data->number_of_philosophers; i++)
		kill(data->pids[i], SIGKILL);
	return (NULL);
}
void	parent_process(t_data *data)
{
	pthread_t death_thread;
	pthread_t finish_thread;
	t_monitor_info info;

	info.data = data;
	info.finished_required = data->number_of_philosophers;

	pthread_create(&death_thread, NULL, death_monitor, data);
	if (data->philo->time.must_eat != -1)
		pthread_create(&finish_thread, NULL, finish_monitor, &info);

	// Wait for all children to terminate
	for (int i = 0; i < data->number_of_philosophers; i++)
		waitpid(data->pids[i], NULL, 0);

	// Cleanup
	cleanup_philosophers(data);
}