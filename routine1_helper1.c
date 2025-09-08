/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:40 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 19:28:53 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->mutex_stop);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	return (stop);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_eaten = get_absolute_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo->data, philo->id, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void	sleep_phase(t_philo *philo)
{
	if (should_stop(philo))
		return ;
	safe_print(philo->data, philo->id, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}
