/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:59:08 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 17:09:04 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_ready_mutex(t_data *input)
{
	input->threads_ready = 0;
	if (pthread_mutex_init(&input->ready_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_mutexes(t_data *input)
{
	int	i;

	if (init_ready_mutex(input) != 0)
		return (free(input->philo), 1);
	if (pthread_mutex_init(&input->mutex_stop, NULL) != 0)
		return (free(input->philo), 1);
	if (pthread_mutex_init(&input->print_mutex, NULL) != 0)
		return (free(input->philo), 1);
	input->mutex_fork = malloc(sizeof(pthread_mutex_t) * input->n_philo);
	if (!input->mutex_fork)
	{
		pthread_mutex_destroy(&input->mutex_stop);
		return (free(input->philo), 1);
	}
	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_mutex_init(&input->mutex_fork[i], NULL) != 0)
		{
			pthread_mutex_destroy(&input->mutex_stop);
			return (free(input->philo), 1);
		}
		i++;
	}
	return (0);
}

int	create_philos(t_data *input)
{
	int	i;

	i = 0;
	input->start_time = get_absolute_time();
	while (i < input->n_philo - 1)
	{
		input->philo[i].id = i + 1;
		input->philo[i].left_fork = i;
		input->philo[i].right_fork = i + 1;
		input->philo[i].meals_eaten = 0;
		input->philo[i].last_meal_eaten = input->start_time;
		input->philo[i].data = input;
		if (pthread_mutex_init(&input->philo[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	input->philo[i].id = i + 1;
	input->philo[i].left_fork = i;
	input->philo[i].right_fork = 0;
	input->philo[i].meals_eaten = 0;
	input->philo[i].last_meal_eaten = input->start_time;
	input->philo[i].data = input;
	if (pthread_mutex_init(&input->philo[i].meal_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		input;
	pthread_t	monitor_thread;

	if (validate_args(argc, argv) != 0 || atol_args(&input, argc, argv) != 0)
		return (1);
	input.philo = malloc(sizeof(t_philo) * input.n_philo);
	if (!input.philo)
		return (1);
	input.stop = 0;
	if (init_mutexes(&input) != 0)
		return (1);
	if (input.n_philo == 1)
		return (one_philo(&input), del_meal_mut(&input), cleanup(&input), 0);
	if (create_philos(&input) != 0)
		return (cleanup(&input), 1);
	if (create_thread_philo(&input) != 0)
		return (del_meal_mut(&input), cleanup(&input), 1);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &input) != 0)
		return (del_meal_mut(&input), free(input.threads), cleanup(&input), 1);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (del_meal_mut(&input), free(input.threads), cleanup(&input), 1);
	if (ft_philo_threads_join(&input) != 0)
		return (del_meal_mut(&input), free(input.threads), cleanup(&input), 1);
	return (del_meal_mut(&input), free(input.threads), cleanup(&input), 0);
}
