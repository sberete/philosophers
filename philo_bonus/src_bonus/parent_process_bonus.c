/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:04:28 by sberete           #+#    #+#             */
/*   Updated: 2025/06/23 20:09:30 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parent_process(t_data *data)
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
}
