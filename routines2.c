// add 42 header

#include "philo.h"

void *monitor_routine(void *data)
{
	t_data *input;
	input = (t_data *)data;

	int i;
	long since_meal;
    while (1)
    {
        i = 0;
        while (i < input->n_philo)
        {
            // Check if simulation should stop
            pthread_mutex_lock(&input->mutex_stop);
            if (input->stop) {
                pthread_mutex_unlock(&input->mutex_stop);
                return (NULL);
            }
            
            // Check if philosopher died
            since_meal = get_absolute_time() - input->philo[i].last_meal_eaten;
            pthread_mutex_unlock(&input->mutex_stop);
            
            if (since_meal >= input->time_to_die) {
                pthread_mutex_lock(&input->mutex_stop);
                if (!input->stop) {
                    input->stop = 1;
                    printf("%ld %d died\n", get_current_time(input), input->philo[i].id);
                }
                pthread_mutex_unlock(&input->mutex_stop);
                return NULL;
            }
            i++;
        }
    }
    return (NULL);
}
