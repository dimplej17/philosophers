/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:19 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 18:00:21 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
            pthread_mutex_lock(&input->mutex_stop);
            if (input->stop) {
                pthread_mutex_unlock(&input->mutex_stop);
                return (NULL);
            }
        pthread_mutex_lock(&input->philo[i].meal_mutex);
		since_meal = get_absolute_time() - input->philo[i].last_meal_eaten;
		pthread_mutex_unlock(&input->philo[i].meal_mutex);
            if (since_meal >= input->time_to_die) {
    if (!input->stop) {
        input->stop = 1;
        // printf("%ld %d died\n", get_current_time(input), input->philo[i].id); pineapple
		safe_print(input, input->philo[i].id,"died");
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

