/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:45 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 18:01:03 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine_one_philo(void *data)
{
	t_philo *philo;
	philo  = (t_philo *)data;

	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
		return (NULL);
	// printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	safe_print(philo->data, philo->id, "has taken a fork");

    while (1)
    {
        if ((get_absolute_time() - philo->last_meal_eaten) >= philo->data->time_to_die)
        {
			if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]) != 0)
				return (NULL);
            // printf("%ld %d died\n", get_current_time(philo->data), philo->id); pineapple
			safe_print(philo->data, philo->id, "died");
            return (NULL);
        }
		usleep(1000);
	}
    return (NULL);
}

void one_philo(t_data *input)
{
	input->philo[0].id = 1;
	input->philo[0].left_fork = 0;
	input->philo[0].right_fork = -1;
	(void)input->philo[0].right_fork;
	input->philo[0].last_meal_eaten = input->start_time;
	input->philo[0].data = input;
	pthread_t t_id1;
	if (pthread_create(&t_id1, NULL, routine_one_philo, &input->philo[0]) != 0)
		return ;
	if (pthread_join(t_id1, NULL) != 0)
		return ;
}

void think_phase(t_philo *philo)
{
	if (should_stop(philo))
		return;
		
	// printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id); pineapple
	safe_print(philo->data, philo->id, "is thinking");
	usleep(1000);
}

void *routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	
	// Stagger even-numbered philosophers to reduce initial contention
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	
	while (!should_stop(philo))
	{
		// Check before taking forks
		if (should_stop(philo))
			break;
			
		if (!take_forks(philo))
			break;
		
		// Check before eating
		if (should_stop(philo))
		{
			drop_forks(philo);
			break;
		}
		
		eat(philo);
		drop_forks(philo);
		
		// Check before sleeping
		if (should_stop(philo))
			break;
			
		sleep_phase(philo);
		
		// Check before thinking
		if (should_stop(philo))
			break;
			
		think_phase(philo);
	}
	return (NULL);
}
