/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:59:34 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 17:59:36 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_philo_threads_join(t_data *input)
{
		int i;
		i = 0;
		while (i < input->n_philo)
	{
		if (pthread_join(input->threads[i], NULL) != 0)
			return (1);
		i++;
	}
		return (0);
}
	
void safe_print(t_data *data, int id, char *msg)
{
    pthread_mutex_lock(&data->print_mutex);
    if (!data->stop)
        printf("%ld %d %s\n", get_current_time(data), id, msg);
    pthread_mutex_unlock(&data->print_mutex);
}
