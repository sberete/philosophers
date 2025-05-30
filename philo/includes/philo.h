/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:18:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/28 19:38:16 by sberete          ###   ########.fr       */
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
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		id;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				must_eat;
	int				name;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	pthread_mutex_t	print_lock;
	t_philo			*philo;
}					t_data;

bool				parsing(t_data data, int argc, char **argv);
t_data				init(int argc, char **argv);

bool				valid_number(char *str);
long				ft_atol(char *str);
long				actual_time(void);

void				philo_routine(t_data *data);

void				clean_philo(t_data *data);

#endif