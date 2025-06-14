/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:42:19 by sberete           #+#    #+#             */
/*   Updated: 2025/06/12 17:37:13 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		id;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				meal_eaten;
	long			last_meal;
	int				must_eat;
	int				name;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
    sem_t           print_lock;
	int				number_of_philosophers;
	int				philos_finished;
	bool			someone_died;
	long			start_time;
	t_philo			*philo;
}					t_data;

bool	data_init(t_data *data, int argc, char **argv);
bool	parsing(t_data data, int argc, char **argv);

#endif
