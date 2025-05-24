/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/24 14:41:21 by sberete          ###   ########.fr       */
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
	t_data *data = (t_data *)arg;
	pthread_t	tid;
	int i;

	i = 0;
	tid = pthread_self();
	while (i < data->number_of_philosophers)
	{
		if (i == 0)
			data->philo[i].left_fork = &data->philo[data->number_of_philosophers - 1].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
		i++;
	}
	// printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
	// 	YELLOW, tid, NC);
	printf("%sThread [%ld] j'ai termine%s\n",
		YELLOW, tid, NC);
	return (NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->count = 0;
	printf("%sCount doit terminer a [%d]%s\n", RED,data->number_of_philosophers * 100, NC);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		pthread_create(&data->philo[i].id, NULL, routine, data);
		data->philo[i].name = i + 1;
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
	printf("%sLa valeur de count est : [%d]%s\n", BYELLOW, data->count,  NC);
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
// int	actual_time(void)
// {
// 	struct timeval	tv;
// 	struct timezone	tz;

// 	gettimeofday(&tv, &tz);
// }
// int	main(void)
// {
// 	printf("Seconde depuis 01/01/1970 : [%ld]\n", tv.tv_sec);
// 	printf("Microseconde : [%ld]\n", tv.tv_usec);

// 	tv.tv_sec -= tv.tv_sec;

// 	printf("Seconde depuis 01/01/1970 : [%ld]\n", tv.tv_sec);
// 	printf("Microseconde : [%ld]\n", tv.tv_usec);
// }