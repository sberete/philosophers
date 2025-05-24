/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:18:20 by sberete           #+#    #+#             */
/*   Updated: 2025/05/24 18:13:19 by sberete          ###   ########.fr       */
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

# define TIMES_TO_COUNT 21000

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	int				name;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				must_eat;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	t_philo			*philo;
}					t_data;

long				ft_atol(char *s);
bool				valid_number(char *str);
bool				parsing(int argc, char **argv);
t_data				init(int argc, char **argv);
long				actual_time(void);

#endif