/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/25 23:03:21 by sxrimu           ###   ########.fr       */
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
 Gestion du time_to_die	❌ À faire	Aucun thread de surveillance, pas de last_meal_time
 Thread de monitoring (mort d’un philosophe)	❌ À faire
 Protection des accès partagés (lecture/écriture last_meal)	❌ À faire	À prévoir avec mutex supplémentaires
 Gestion du cas avec 1 seul philosophe	❌ À faire
 Fin propre de la simulation (stop tous les threads)	❌ À faire
*/
void print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%ld %d %s\n", actual_time(), philo->name, action);
	pthread_mutex_unlock(philo->print_lock);
}
void	*routine(void *arg)
{
	t_philo		*philo;
	// int eat_count;
	
	philo = (t_philo *)arg;
	// eat_count = 0;
	// while (!is_dead && (philo->must_eat == -1 || eat_count < philo->must_eat))
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%s%ld %d has taken a fork%s\n", BYELLOW, actual_time(),
	philo->name, NC);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%s%ld %d has taken a fork%s\n", BYELLOW, actual_time(),
			philo->name, NC);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->print_lock);
	printf("%s%ld %d is eating%s\n", GREEN, actual_time(), philo->name, NC);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%s%ld %d is sleeping%s\n", RED, actual_time(), philo->name, NC);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_sleep * 1000);
	pthread_mutex_lock(philo->print_lock);
	printf("%s%ld %d is thinking%s\n", NC, actual_time(), philo->name, NC);
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

void	thread_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philo[i].name % 2 == 0)
			usleep(1000 * 1000);
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
	{
		pthread_join(data->philo[i].id, NULL);
		pthread_mutex_destroy(&data->philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv))
	{
		data = init(argc, argv);
		thread_routine(&data);
	}
	else
		printf("Error\n");
}
