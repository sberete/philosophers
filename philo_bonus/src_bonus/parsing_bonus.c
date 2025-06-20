/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:23 by sberete           #+#    #+#             */
/*   Updated: 2025/06/20 20:00:48 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	parsing(t_data data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (false);
	if (data.number_of_philosophers > 200 || data.philo->time.to_die < 60
		|| data.philo->time.to_sleep < 60 || data.philo->time.to_eat < 60)
		return (false);
	i = 1;
	while (argv[i])
	{
		if (valid_number(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
