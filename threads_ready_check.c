/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_ready_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 02:45:41 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 02:45:55 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_ready(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->ready_mutex);
		if (data->threads_ready >= data->n_philo)
		{
			pthread_mutex_unlock(&data->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->ready_mutex);
		usleep(10);
	}
}

void	mark_thread_ready(t_data *data)
{
	pthread_mutex_lock(&data->ready_mutex);
	data->threads_ready++;
	pthread_mutex_unlock(&data->ready_mutex);
}
