/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:16 by sberete           #+#    #+#             */
/*   Updated: 2025/06/08 22:37:03 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 Gestion du must_eat 	❌ À faire	Pas encore traité dans le philo
 Gestion du time_to_die	❌ À faire	Aucun thread de surveillance
 Thread de monitoring (mort d’un philosophe)	❌ À faire
 Gestion du cas avec 1 seul philosophe	❌ À faire
 Fin propre de la simulation (stop tous les threads)	❌ À faire
*/

static void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->someone_died_lock);
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", actual_time() - philo->data->start_time,
			philo->name, action);
	pthread_mutex_unlock(&philo->data->someone_died_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	holding_forks(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}
static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->name % 2 == 0)
		usleep(100);
	while (philo->must_eat == -1 || philo->meal_eaten < philo->must_eat)
	{
		pthread_mutex_lock(&philo->data->someone_died_lock);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->someone_died_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->someone_died_lock);
		holding_forks(philo);
		pthread_mutex_lock(&philo->last_meal_lock);
		philo->last_meal = actual_time();
		pthread_mutex_unlock(&philo->last_meal_lock);
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->meal_eaten_lock);
		philo->meal_eaten++;
		pthread_mutex_unlock(&philo->meal_eaten_lock);
		// pthread_mutex_lock(&philo->data->someone_died_lock);
		// if (philo->data->someone_died)
		// {
		// 	if (philo->name % 2 == 0)
		// 	{
		// 		pthread_mutex_unlock(&philo->right_fork);
		// 		pthread_mutex_unlock(philo->left_fork);
		// 	}
		// 	else
		// 	{
		// 		pthread_mutex_unlock(philo->left_fork);
		// 		pthread_mutex_unlock(&philo->right_fork);
		// 	}
		// 	pthread_mutex_unlock(&philo->data->someone_died_lock);
		// 	break ;
		// }
		// pthread_mutex_unlock(&philo->data->someone_died_lock);

		ft_sleep(philo->time_to_eat, philo->data);
		if (philo->name % 2 == 0)
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		// pthread_mutex_lock(&philo->data->someone_died_lock);
		// if (philo->data->someone_died)
		// {
		// 	pthread_mutex_unlock(&philo->data->someone_died_lock);
		// 	break ;
		// }
		// pthread_mutex_unlock(&philo->data->someone_died_lock);

		print_action(philo, "is sleeping");
		ft_sleep(philo->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	philo_routine(t_data *data)
{
	int			i;
	pthread_t	monitoring;

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
	clean_philo(data);
}
