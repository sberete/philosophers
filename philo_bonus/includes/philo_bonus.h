/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:42:19 by sberete           #+#    #+#             */
/*   Updated: 2025/06/20 19:45:27 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_time
{
	int				to_sleep;
	int				to_eat;
	int				to_die;
	int				must_eat;
}					t_time;

typedef struct s_sem
{
	sem_t			*print_lock;
	sem_t			*fork;
	sem_t			*died;
	sem_t			*finished;
}					t_sem;

typedef struct s_philo
{
	pthread_mutex_t	meal_mutex;
	t_time			time;
	int				meal_eaten;
	long			last_meal;
	int				name;
	bool			a;
	pid_t			pid;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_sem			sem;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	int				number_of_philosophers;
	long			start_time;
	t_philo			*philo;
	pid_t			*pids;
}					t_data;

bool				data_init(t_data *data, int argc, char **argv);
bool				parsing(t_data data, int argc, char **argv);
long				ft_atol(char *str);
long				actual_time(void);
bool				valid_number(char *str);
void				child_process(t_philo *philo);
void				ft_sleep(long ms, t_data *data);
void				parent_process(t_data *data);
void				print_error(t_data *data, char *action);

#endif
