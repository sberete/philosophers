/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:03:04 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 22:45:47 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	holding_forks(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	fork_release(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static int	has_someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->someone_died_lock);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->someone_died_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->someone_died_lock);
	return (0);
}

static bool	handle_eating(t_philo *philo)
{
	if (has_someone_died(philo) == 1)
	{
		fork_release(philo);
		return (true);
	}
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = actual_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_eaten_lock);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_eaten_lock);
	if (philo->must_eat != -1 && philo->meal_eaten == philo->must_eat)
	{
		pthread_mutex_lock(&philo->data->finish_lock);
		philo->data->philos_finished++;
		pthread_mutex_unlock(&philo->data->finish_lock);
	}
	if (philo->data->philos_finished == philo->data->number_of_philosophers)
	{
		fork_release(philo);
		return (true);
	}
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (handle_single_philosopher(philo))
		return (NULL);
	if (philo->name % 2 == 0)
		usleep(100);
	while (true)
	{
		if (has_someone_died(philo) == 1)
			break ;
		holding_forks(philo);
		if (handle_eating(philo))
			break ;
		ft_sleep(philo->time_to_eat, philo->data);
		fork_release(philo);
		print_action(philo, "is sleeping");
		if (has_someone_died(philo) == 1)
			break ;
		ft_sleep(philo->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
