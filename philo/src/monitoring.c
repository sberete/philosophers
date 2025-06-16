/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:33:41 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 22:36:09 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d died\n", actual_time() - philo->data->start_time,
		philo->name);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static bool	have_all_philosophers_finished(t_data *data)
{
	pthread_mutex_lock(&data->finish_lock);
	if (data->philos_finished == data->number_of_philosophers)
	{
		pthread_mutex_unlock(&data->finish_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->finish_lock);
	return (false);
}

static void	mark_philosopher_as_dead(t_data *data)
{
	pthread_mutex_lock(&data->someone_died_lock);
	data->someone_died = true;
	pthread_mutex_unlock(&data->someone_died_lock);
}

void	*monitor(void *arg)
{
	t_data	*data;
	long	last_meal_time;
	int		i;

	data = (t_data *)arg;
	while (true)
	{
		if (have_all_philosophers_finished(data))
			return (NULL);
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->philo[i].last_meal_lock);
			last_meal_time = actual_time() - data->philo[i].last_meal;
			pthread_mutex_unlock(&data->philo[i].last_meal_lock);
			if (last_meal_time > data->philo[i].time_to_die)
			{
				mark_philosopher_as_dead(data);
				print_death(&data->philo[i]);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
}
