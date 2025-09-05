// add 42 header

#include "philo.h"

long get_current_time(t_data *data)
{
	return (get_absolute_time() - data->start_time);
}

// int should_stop(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->mutex_stop);
//     int stop = philo->data->stop;
//     pthread_mutex_unlock(&philo->data->mutex_stop);
//     return (stop);
// }

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