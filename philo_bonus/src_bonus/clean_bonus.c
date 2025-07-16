/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:06:59 by sberete           #+#    #+#             */
/*   Updated: 2025/06/23 21:22:56 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->philo[i++].meal_mutex);
	if (data->sem.fork != SEM_FAILED)
		sem_close(data->sem.fork);
	if (data->sem.print_lock != SEM_FAILED)
		sem_close(data->sem.print_lock);
	if (data->sem.died != SEM_FAILED)
		sem_close(data->sem.died);
	if (data->sem.finished != SEM_FAILED)
		sem_close(data->sem.finished);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/died");
	sem_unlink("/philo_finished");
	if (data->philo)
		free(data->philo);
	if (data->pids)
		free(data->pids);
}
