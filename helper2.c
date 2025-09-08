// add 42 header

#include "philo.h"

long get_current_time(t_data *data)
{
	return (get_absolute_time() - data->start_time);
}

int check_all_eaten_enough(t_data *input)
{
    int i = 0;
    
    while (i < input->n_philo)
    {
        if (input->philo[i].meals_eaten < input->must_eat)
            return (0);  // At least one philosopher hasn't eaten enough
        i++;
    }
    return (1);  // All philosophers have eaten enough meals
}

void cleanup(t_data *data)
{
    int i;
	i = 0;
    while (i < data->n_philo)
        pthread_mutex_destroy(&data->mutex_fork[i++]);
    pthread_mutex_destroy(&data->mutex_stop);
    free(data->mutex_fork);
    free(data->philo);
}

void destroy_meal_mutex(t_data *data)
{
	int i;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
}

int create_thread_philo(t_data *input)
{
	int i;
	input->threads = malloc(sizeof(pthread_t) * input->n_philo);
	if (!input->threads)
		return (1);
	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_create(&input->threads[i], NULL, routine, &input->philo[i]) != 0)
			return (free(input->threads), 1);
		i++;
	}
	return (0);
}

int ft_philo_threads_join(t_data *input)
	{
		int i;
		i = 0;
		while (i < input->n_philo)
	{
		if (pthread_join(input->threads[i], NULL) != 0)
			return (1);
		i++;
	}
		return (0);
	}
	