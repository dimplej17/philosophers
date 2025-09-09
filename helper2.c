/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:39:30 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 17:10:29 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eaten_enough(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->n_philo)
	{
		pthread_mutex_lock(&input->philo[i].meal_mutex);
		if (input->philo[i].meals_eaten < input->must_eat)
		{
			pthread_mutex_unlock(&input->philo[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&input->philo[i].meal_mutex);
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&data->mutex_fork[i++]);
	pthread_mutex_destroy(&data->mutex_stop);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->ready_mutex);
	free(data->mutex_fork);
	free(data->philo);
}

void	del_meal_mut(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
}

int	create_thread_philo(t_data *input)
{
	int	i;

	input->threads = malloc(sizeof(pthread_t) * input->n_philo);
	if (!input->threads)
		return (1);
	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_create(&input->threads[i], NULL, routine,
				&input->philo[i]) != 0)
			return (free(input->threads), 1);
		i++;
	}
	return (0);
}
