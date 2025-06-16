#include "philo_bonus.h"

void parent_process(t_data *data)
{
    int i;
    
    i = 0;
	while (i < data->number_of_philosophers)
		waitpid(data->pids[i++], NULL, 0);
	sem_close(data->fork);
	sem_close(data->print_lock);
	sem_unlink("/forks");
	sem_unlink("/print");
	free(data->philo);
	free(data->pids);
}