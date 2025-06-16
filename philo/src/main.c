/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/06/16 22:46:49 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!data_init(&data, argc, argv) || !parsing(data, argc, argv))
	{
		free(data.philo);
		printf("Error\n");
		return (1);
	}
	run_philosophers_simulation(&data);
}
