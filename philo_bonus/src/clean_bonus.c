/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:05:53 by sberete           #+#    #+#             */
/*   Updated: 2025/06/11 21:16:57 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		// pthread_mutex_destroy(&data->philo[i].right_fork);
		// pthread_mutex_destroy(&data->philo[i].meal_eaten_lock);
		// pthread_mutex_destroy(&data->philo[i].last_meal_lock);
		i++;
	}
	// pthread_mutex_destroy(&data->print_lock);
	// pthread_mutex_destroy(&data->someone_died_lock);
	// pthread_mutex_destroy(&data->finish_lock);
	free(data->philo);
}
