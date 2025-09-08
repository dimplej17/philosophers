/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:19 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 22:53:26 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_data *input, int i)
{
	long	since_meal;

	pthread_mutex_lock(&input->philo[i].meal_mutex);
	since_meal = get_absolute_time() - input->philo[i].last_meal_eaten;
	pthread_mutex_unlock(&input->philo[i].meal_mutex);
	if (since_meal >= input->time_to_die)
		return (handle_death(input, i));
	return (0);
}

int	monitor_all_philosophers(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->n_philo)
	{
		if (check_stop_status(input))
			return (1);
		if (check_philosopher_death(input, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_eating_completion(t_data *input)
{
	if (input->must_eat > 0 && check_all_eaten_enough(input))
	{
		pthread_mutex_lock(&input->mutex_stop);
		input->stop = 1;
		pthread_mutex_unlock(&input->mutex_stop);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *data)
{
	t_data	*input;

	input = (t_data *)data;
	while (1)
	{
		if (monitor_all_philosophers(input))
			return (NULL);
		if (check_eating_completion(input))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
