/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:45:32 by sberete           #+#    #+#             */
/*   Updated: 2025/06/20 19:56:58 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long ms, t_data *data)
{
	long	start;

	start = actual_time();
	while ((actual_time() - start) < ms)
	{
		pthread_mutex_lock(&data->mutex.someone_died_lock);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->mutex.someone_died_lock);
			break ;
		}
		pthread_mutex_unlock(&data->mutex.someone_died_lock);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->mutex.print_lock);
	pthread_mutex_lock(&philo->data->mutex.someone_died_lock);
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", actual_time() - philo->data->start_time,
			philo->name, action);
	pthread_mutex_unlock(&philo->data->mutex.someone_died_lock);
	pthread_mutex_unlock(&philo->data->mutex.print_lock);
}

bool	handle_single_philosopher(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->mutex.left_fork);
		print_action(philo, "has taken a fork");
		ft_sleep(philo->time.to_die, philo->data);
		pthread_mutex_unlock(philo->mutex.left_fork);
		return (true);
	}
	return (false);
}
