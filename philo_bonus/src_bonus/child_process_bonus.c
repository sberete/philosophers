#include "philo_bonus.h"

static void	print_action(t_philo *philo, char *action)
{
	sem_wait(philo->data->print_lock);
	printf("%ld %d %s\n", actual_time() - philo->data->start_time, philo->name,
		action);
	sem_post(philo->data->print_lock);
}
static void	single_philo(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print_action(philo, "has taken a fork");
	ft_sleep(philo->time_to_die, philo->data);
	sem_post(philo->data->fork);
	exit(EXIT_SUCCESS);
}

void	child_process(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
		single_philo(philo);
	if (philo->name % 2 == 0)
		usleep(200);
	while (true)
	{
		sem_wait(philo->data->fork);
		print_action(philo, "has taken a fork");
		sem_wait(philo->data->fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		philo->meal_eaten++;
		// if (philo->must_eat != -1 && philo->meal_eaten == philo->must_eat)
		// 	philo->data->philos_finished++;
		// if (philo->data->philos_finished == philo->data->number_of_philosophers)
		// {
		// 	sem_post(philo->data->fork);
		// 	sem_post(philo->data->fork);
		// 	break ;
		// }
		ft_sleep(philo->time_to_eat, philo->data);
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
		print_action(philo, "is sleeping");
		ft_sleep(philo->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	exit(EXIT_SUCCESS);
}
