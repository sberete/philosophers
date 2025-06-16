/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:41:45 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 20:14:22 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!data_init(&data, argc, argv) || !parsing(data, argc, argv))
	{
		free(data.philo);
		free(data.pids);
		printf("Error\n");
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		data.pids[i] = fork();
		if (data.pids[i] == -1)
			exit(EXIT_FAILURE);
		if (data.pids[i] == 0)
			child_process(&data.philo[i]);
		i++;
	}
	parent_process(&data);
}
