/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:08:36 by sberete           #+#    #+#             */
/*   Updated: 2025/06/18 20:23:02 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void print_error(t_data *data, char *action)
{
    free(data->pids);
    free(data->philo);
    printf("%s\n", action);
    exit(EXIT_FAILURE);
}