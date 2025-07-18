/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:05:53 by sberete           #+#    #+#             */
/*   Updated: 2025/07/18 19:10:18 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].mutex.right_fork);
		pthread_mutex_destroy(&data->philo[i].mutex.meal_eaten_lock);
		pthread_mutex_destroy(&data->philo[i].mutex.last_meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->mutex.print_lock);
	pthread_mutex_destroy(&data->mutex.someone_died_lock);
	pthread_mutex_destroy(&data->mutex.finish_lock);
	free(data->philo);
}

