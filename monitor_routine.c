// add 42 header

#include "philo.h"

void *monitor_routine(void *data)
{
    t_data *input = (t_data *)data;
    int i;
    long since_meal;
    
    while (1)
    {
        i = 0;
        while (i < input->n_philo)
        {
            pthread_mutex_lock(&input->mutex_stop);
            if (input->stop) {
                pthread_mutex_unlock(&input->mutex_stop);
                return (NULL);
            }
        since_meal = get_absolute_time() - input->philo[i].last_meal_eaten;
            if (since_meal >= input->time_to_die) {
    if (!input->stop) {
        input->stop = 1;
        printf("%ld %d died\n", get_current_time(input), input->philo[i].id);
    }
    pthread_mutex_unlock(&input->mutex_stop);
    return (NULL);

            }
            pthread_mutex_unlock(&input->mutex_stop);
            i++;
        }
        // Check if all have eaten enough (if must_eat is specified)
        if (input->must_eat > 0 && check_all_eaten_enough(input)) {
            pthread_mutex_lock(&input->mutex_stop);
            input->stop = 1;
            pthread_mutex_unlock(&input->mutex_stop);
            return (NULL);
        }
        usleep(500); // Small delay between checks
    }
    return (NULL);
}

