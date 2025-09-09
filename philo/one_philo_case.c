/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 02:39:58 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 02:40:26 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one_philo(void *data)
{
	t_philo	*philo;
	long	time_since_meal;

	philo = (t_philo *)data;
	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
		return (NULL);
	safe_print(philo->data, philo->id, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		time_since_meal = get_absolute_time() - philo->last_meal_eaten;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (time_since_meal >= philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
			safe_print(philo->data, philo->id, "died");
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	one_philo(t_data *input)
{
	pthread_t	t_id1;

	input->start_time = get_absolute_time();
	input->philo[0].id = 1;
	input->philo[0].left_fork = 0;
	input->philo[0].right_fork = -1;
	(void)input->philo[0].right_fork;
	input->philo[0].meals_eaten = 0;
	input->philo[0].last_meal_eaten = input->start_time;
	input->philo[0].data = input;
	if (pthread_mutex_init(&input->philo[0].meal_mutex, NULL) != 0)
		return ;
	if (pthread_create(&t_id1, NULL, routine_one_philo, &input->philo[0]) != 0)
		return ;
	if (pthread_join(t_id1, NULL) != 0)
		return ;
}
