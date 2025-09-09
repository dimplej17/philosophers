/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:45 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 02:45:11 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	prepare_philosopher(t_philo *philo)
{
	mark_thread_ready(philo->data);
	wait_all_ready(philo->data);
	if (philo->id % 2 == 0)
		smart_sleep(philo->data->time_to_eat / 2, philo);
}

static int	attempt_eating(t_philo *philo)
{
	if (should_stop(philo))
		return (0);
	if (!take_forks(philo))
		return (0);
	if (should_stop(philo))
	{
		drop_forks(philo);
		return (0);
	}
	eat(philo);
	return (1);
}

static int	attempt_sleeping(t_philo *philo)
{
	if (should_stop(philo))
		return (0);
	sleep_phase(philo);
	return (1);
}

static int	attempt_thinking(t_philo *philo)
{
	if (should_stop(philo))
		return (0);
	think_phase(philo);
	return (1);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	prepare_philosopher(philo);
	while (!should_stop(philo))
	{
		if (!attempt_eating(philo))
			break ;
		if (!attempt_sleeping(philo))
			break ;
		if (!attempt_thinking(philo))
			break ;
	}
	return (NULL);
}

// void	*routine(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	mark_thread_ready(philo->data);
// 	wait_all_ready(philo->data);
// 	if (philo->id % 2 == 0)
// 		smart_sleep(philo->data->time_to_eat / 2, philo);
// 	while (!should_stop(philo))
// 	{
// 		if (should_stop(philo))
// 			break ;
// 		if (!take_forks(philo))
// 			break ;
// 		if (should_stop(philo))
// 		{
// 			drop_forks(philo);
// 			break ;
// 		}
// 		eat(philo);
// 		if (should_stop(philo))
// 			break ;
// 		sleep_phase(philo);
// 		if (should_stop(philo))
// 			break ;
// 		think_phase(philo);
// 	}
// 	return (NULL);
// }
