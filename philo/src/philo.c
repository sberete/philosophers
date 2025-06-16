/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:16 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 22:46:42 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_philosophers_simulation(t_data *data)
{
	pthread_t	monitoring;
	int			i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i == 0)
			data->philo[i].left_fork = &data->philo[data->number_of_philosophers
				- 1].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
		pthread_create(&data->philo[i].id, NULL, routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, monitor, data);
	i = 0;
	while (i < data->number_of_philosophers)
		pthread_join(data->philo[i++].id, NULL);
	pthread_join(monitoring, NULL);
	cleanup_philosophers(data);
}
