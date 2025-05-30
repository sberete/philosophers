/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:16 by sberete           #+#    #+#             */
/*   Updated: 2025/05/28 19:37:32 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not overlap with another message.
• A message announcing a philosopher’s death must be displayed within 10 ms of
their actual death.
• Again, philosophers should avoid dying!
*/

/*
 Gestion du cycle eating → sleeping → thinking	❌ À faire
 Gestion du must_eat 	❌ À faire	Pas encore traité dans le philo
 Gestion du time_to_die	❌ À faire	Aucun thread de surveillance,
		->	pas de last_meal_time
 Thread de monitoring (mort d’un philosophe)	❌ À faire
 Protection des accès partagés (lecture/écriture last_meal)	❌ À faire	À prévoir avec mutex supplémentaires
 Gestion du cas avec 1 seul philosophe	❌ À faire
 Fin propre de la simulation (stop tous les threads)	❌ À faire
*/

static void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%ld %d %s\n", actual_time(), philo->name, action);
	pthread_mutex_unlock(philo->print_lock);
}

// static int is_dead(t_data *data)
// {
// 	int i = 0;
// 	while (i < 0)
// 	{
// 		/* code */
// 	}
// }

static void	*routine(void *arg)
{
	t_philo	*philo;

	// int eat_count;
	philo = (t_philo *)arg;
	if (philo->name % 2 == 0)
		usleep(100 * 1000);
	// eat_count = 0;
	// while (!is_dead && (philo->must_eat == -1
	// 		|| eat_count < philo->must_eat))
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	print_action(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	print_action(philo, "is thinking");
	return (NULL);
}

void	philo_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i == 0)
			data->philo[i].left_fork = &data->philo[data->number_of_philosophers
				- 1].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
		data->philo[i].print_lock = &data->print_lock;
		pthread_create(&data->philo[i].id, NULL, routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
		pthread_join(data->philo[i++].id, NULL);
	clean_philo(data);
}
