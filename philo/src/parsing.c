/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:23 by sberete           #+#    #+#             */
/*   Updated: 2025/06/19 16:34:21 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parsing(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
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
