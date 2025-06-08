/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:20 by sberete           #+#    #+#             */
/*   Updated: 2025/06/05 19:48:04 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init(&data, argc, argv) || !parsing(data, argc, argv))
	{
		free(data.philo);
		printf("Error\n");
		return (1);
	}
	philo_routine(&data);
}
