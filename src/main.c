/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/16 16:51:21 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	pthread_t	tid;

	(void)arg;
	tid = pthread_self();
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
		YELLOW, tid, NC);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	data = init(argc, argv);
	if (parsing(data, argc, argv))
	{
		int i = 0;
		while (i < data.number_of_philosophers)
		{
			pthread_create(&data.ap[i], NULL, routine, NULL);
			printf("Main: Creation du thread [%d] thread [%ld]\n", i,
				data.ap[i]);
			i++;
		}
		i = 0;
		while (i < data.number_of_philosophers)
		{
			pthread_join(data.ap[i], NULL);
			printf("Main: Union du  thread [%d] [%ld]\n", i, data.ap[i]);
			i++;
		}
	}
	else
		printf("Error\n");
}