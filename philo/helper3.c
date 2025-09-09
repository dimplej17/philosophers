/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:59:34 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 22:53:09 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_threads_join(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_join(input->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	safe_print(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->mutex_stop);
	if (!data->stop)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d %s\n", get_current_time(data), id, msg);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->mutex_stop);
}

int	check_stop_status(t_data *input)
{
	pthread_mutex_lock(&input->mutex_stop);
	if (input->stop)
	{
		pthread_mutex_unlock(&input->mutex_stop);
		return (1);
	}
	pthread_mutex_unlock(&input->mutex_stop);
	return (0);
}

int	handle_death(t_data *input, int i)
{
	pthread_mutex_lock(&input->mutex_stop);
	if (!input->stop)
	{
		input->stop = 1;
		pthread_mutex_lock(&input->print_mutex);
		printf("%ld %d died\n", get_current_time(input), input->philo[i].id);
		pthread_mutex_unlock(&input->print_mutex);
	}
	pthread_mutex_unlock(&input->mutex_stop);
	return (1);
}
