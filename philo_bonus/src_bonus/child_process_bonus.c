/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:04:38 by sberete           #+#    #+#             */
/*   Updated: 2025/07/19 21:59:27 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	single_philo(t_philo *philo)
{
	sem_wait(philo->data->sem.fork);
	print_action(philo, "has taken a fork");
	ft_sleep(philo->time.to_die, philo);
	sem_post(philo->data->sem.fork);
	print_action(philo, "died");
	sem_post(philo->data->sem.died);
	exit(EXIT_SUCCESS);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if ((actual_time() - philo->last_meal) > philo->time.to_die)
		{
			print_action(philo, "died");
			pthread_mutex_unlock(&philo->meal_mutex);
			sem_post(philo->data->sem.died);
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(1000);
	}
	return (NULL);
}

static void	handle_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = actual_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->time.must_eat != -1 && philo->meal_eaten >= philo->time.must_eat
		&& !philo->a)
	{
		sem_post(philo->data->sem.finished);
		philo->a = true;
	}
}

static void	holding_forks(t_philo *philo)
{
	sem_wait(philo->data->sem.fork);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->sem.fork);
	print_action(philo, "has taken a fork");
}

void	child_process(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->data->number_of_philosophers == 1)
		single_philo(philo);
	if (pthread_create(&monitor, NULL, monitor_routine, philo))
		print_error(philo->data, "pthread_create failed");
	pthread_detach(monitor);
	if (philo->name % 2 == 0)
		usleep(100);
	while (true)
	{
		sem_wait(philo->data->sem.active);
		holding_forks(philo);
		handle_eating(philo);
		ft_sleep(philo->time.to_eat, philo);
		sem_post(philo->data->sem.fork);
		sem_post(philo->data->sem.fork);
		sem_post(philo->data->sem.active);
		print_action(philo, "is sleeping");
		ft_sleep(philo->time.to_sleep, philo);
		print_action(philo, "is thinking");
		usleep(50);
	}
	exit(EXIT_SUCCESS);
}
