/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:04:38 by sberete           #+#    #+#             */
/*   Updated: 2025/06/20 20:02:40 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_action(t_philo *philo, char *action)
{
	sem_wait(philo->data->sem.print_lock);
	printf("%ld %d %s\n", actual_time() - philo->data->start_time, philo->name,
		action);
	sem_post(philo->data->sem.print_lock);
}

static void	single_philo(t_philo *philo)
{
	sem_wait(philo->data->sem.fork);
	print_action(philo, "has taken a fork");
	ft_sleep(philo->time.to_die, philo->data);
	sem_post(philo->data->sem.fork);
	print_action(philo, "died");
	sem_post(philo->data->sem.died);
	exit(EXIT_SUCCESS);
}

void *monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long last_meal_copy;

    while (1)
    {
        usleep(1000);
        pthread_mutex_lock(&philo->meal_mutex);
        last_meal_copy = philo->last_meal;
        pthread_mutex_unlock(&philo->meal_mutex);
        if ((actual_time() - last_meal_copy) > philo->time.to_die)
        {
            pthread_mutex_lock(&philo->data->death_mutex);
            if (!philo->data->someone_died)
            {
                philo->data->someone_died = 1;
                print_action(philo, "died");
                sem_post(philo->data->sem.died);
            }
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_lock(&philo->meal_mutex);
        if (philo->time.must_eat != -1 && philo->meal_eaten >= philo->time.must_eat)
        {
            pthread_mutex_unlock(&philo->meal_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->meal_mutex);
    }
    return (NULL);
}


void	child_process(t_philo *philo)
{
	pthread_t	death;

	if (philo->data->number_of_philosophers == 1)
		single_philo(philo);
	if (philo->name % 2 == 0)
		usleep(200);
	pthread_create(&death, NULL, monitor, philo);
	pthread_detach(death);
	while (true)
	{
		sem_wait(philo->data->sem.fork);
		print_action(philo, "has taken a fork");
		sem_wait(philo->data->sem.fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = actual_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (philo->time.must_eat != -1 && philo->meal_eaten >= philo->time.must_eat
			&& !philo->a)
		{
			sem_post(philo->data->sem.finished);
			philo->a = true;
		}
		ft_sleep(philo->time.to_eat, philo->data);
		sem_post(philo->data->sem.fork);
		sem_post(philo->data->sem.fork);
		print_action(philo, "is sleeping");
		ft_sleep(philo->time.to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	exit(EXIT_SUCCESS);
}
