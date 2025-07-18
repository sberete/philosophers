/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:18:20 by sberete           #+#    #+#             */
/*   Updated: 2025/07/18 19:01:19 by sberete          ###   ########.fr       */
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

typedef struct s_time
{
	int				to_sleep;
	int				to_eat;
	int				to_die;
	int				must_eat;
}					t_time;

typedef struct s_philo_mutex
{
	pthread_mutex_t	meal_eaten_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo_mutex;

typedef struct s_philo
{
	t_philo_mutex	mutex;
	t_time			time;
	pthread_t		id;
	int				meal_eaten;
	long			last_meal;
	int				name;
	struct s_data	*data;
}					t_philo;

typedef struct s_data_mutex
{
	pthread_mutex_t	someone_died_lock;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	print_lock;
}					t_data_mutex;

typedef struct s_data
{
	t_data_mutex	mutex;
	t_philo			*philo;
	int				number_of_philo;
	int				philos_finished;
	bool			someone_died;
	long			start_time;
}					t_data;

bool				parsing(int argc, char **argv);
bool				data_init(t_data *data, int argc, char **argv);
bool				valid_number(char *str);
long				ft_atol(char *str);
long				actual_time(void);
void				ft_sleep(long ms, t_data *data);
void				*monitor(void *arg);
void				*routine(void *arg);
void				run_philosophers_simulation(t_data *data);
void				print_action(t_philo *philo, char *action);
bool				handle_single_philosopher(t_philo *philo);
void				cleanup_philosophers(t_data *data);

#endif