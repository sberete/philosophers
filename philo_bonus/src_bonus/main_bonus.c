/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:41:45 by sberete           #+#    #+#             */
/*   Updated: 2025/06/23 21:13:16 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!data_init(&data, argc, argv) || !parsing(data, argc, argv))
		print_error(&data, "Error");
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
