/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxrimu <sxrimu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:18:20 by sberete           #+#    #+#             */
/*   Updated: 2025/06/01 21:58:30 by sxrimu           ###   ########.fr       */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		id;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	pthread_mutex_t	meal_eaten_lock;
	int				meal_eaten;
	// long			last_meal;
	int				must_eat;
	int				name;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	print_lock;
	int				number_of_philosophers;
	pthread_mutex_t	someone_died_lock;
	bool			someone_died;
	long			start_time;
	t_philo			*philo;
}					t_data;

bool				parsing(t_data data, int argc, char **argv);
bool				init(t_data *data, int argc, char **argv);

bool				valid_number(char *str);
long				ft_atol(char *str);
long				actual_time(void);

void				philo_routine(t_data *data);

void				clean_philo(t_data *data);

#endif