/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:41:45 by sberete           #+#    #+#             */
/*   Updated: 2025/07/19 21:56:32 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!parsing(argc, argv) || !data_init(&data, argc, argv))
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		data.pids[i] = fork();
		if (data.pids[i] == -1)
			print_error(&data, "Fork() failure");
		if (data.pids[i] == 0)
			child_process(&data.philo[i]);
		i++;
	}
	parent_process(&data);
}
