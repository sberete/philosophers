/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/24 22:11:06 by sberete          ###   ########.fr       */
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
Fairez
*/

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)arg;
	tid = pthread_self();
	// pthread_mutex_lock(&philo->right_fork);
	// pthread_mutex_lock(philo->left_fork);
	if (pthread_mutex_lock(&philo->right_fork) == 0
		&& pthread_mutex_lock(philo->left_fork) == 0)
		printf("%s%ld %d has taken a fork%s\n", BYELLOW, actual_time(),
			philo->name, NC);
	// unlock la fourchette gauche
	printf("%s%ld %d is eating%s\n", GREEN, actual_time(), philo->name, NC);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	// printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
	// 	YELLOW, tid, NC);
	return (NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		// if (data->philo[i].name % 2 == 0)
		// 	usleep(500);
		if (i == 0)
			data->philo[i].left_fork = &data->philo[data->number_of_philosophers
				- 1].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
		pthread_create(&data->philo[i].id, NULL, routine, &data->philo[i]);
		printf("Main: Creation du thread [%d] id : [%ld]\n",
			data->philo[i].name, data->philo[i].id);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo[i].id, NULL);
		pthread_mutex_destroy(&data->philo[i].right_fork);
		printf("Main: Union du thread [%d] [%ld]\n", data->philo[i].name,
			data->philo[i].id);
		i++;
	}
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv))
	{
		data = init(argc, argv);
		create_thread(&data);
	}
	else
		printf("Error\n");
}
