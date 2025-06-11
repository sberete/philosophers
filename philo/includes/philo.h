/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:18:20 by sberete           #+#    #+#             */
/*   Updated: 2025/06/10 21:01:10 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	meal_eaten_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
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
	pthread_mutex_t	someone_died_lock;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	print_lock;
	int				number_of_philosophers;
	int				philos_finished;
	bool			someone_died;
	long			start_time;
	t_philo			*philo;
}					t_data;

bool				parsing(t_data data, int argc, char **argv);
bool				init(t_data *data, int argc, char **argv);

bool				valid_number(char *str);
long				ft_atol(char *str);
long				actual_time(void);
void				ft_sleep(long ms, t_data *data);
void				*monitor(void *arg);
void				*routine(void *arg);

void				philo_routine(t_data *data);
void				print_action(t_philo *philo, char *action);

void				clean_philo(t_data *data);

#endif