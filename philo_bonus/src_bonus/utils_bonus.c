/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:37 by sberete           #+#    #+#             */
/*   Updated: 2025/07/17 20:52:07 by sxrimu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

bool	valid_number(char *str)
{
	long long	val;
	int			i;

	i = 0;
	val = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (false);
		i++;
	}
	if (str[i] == '\0')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		val = val * 10 + (str[i] - '0');
		if (val > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

long	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ft_sleep(long ms, t_philo *philo)
{
	long	start;

	start = actual_time();
	while ((actual_time() - start) < ms)
	{
		// Vérifier si le philosophe est mort
		pthread_mutex_lock(&philo->meal_mutex);
		if ((actual_time() - philo->last_meal) > philo->time.to_die)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			print_action(philo, "died");
			sem_post(philo->data->sem.died);
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(100);
	}
}
