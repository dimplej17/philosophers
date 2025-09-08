/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:29:17 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 19:29:27 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	determine_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static int	take_first_fork(t_philo *philo, int first_fork)
{
	if (should_stop(philo))
		return (0);
	if (pthread_mutex_lock(&philo->data->mutex_fork[first_fork]) != 0)
		return (0);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	safe_print(philo->data, philo->id, "has taken a fork");
	return (1);
}

static int	take_second_fork(t_philo *philo, int first_fork, int second_fork)
{
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	if (pthread_mutex_lock(&philo->data->mutex_fork[second_fork]) != 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		pthread_mutex_unlock(&philo->data->mutex_fork[second_fork]);
		return (0);
	}
	safe_print(philo->data, philo->id, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	determine_fork_order(philo, &first_fork, &second_fork);
	if (!take_first_fork(philo, first_fork))
		return (0);
	if (!take_second_fork(philo, first_fork, second_fork))
		return (0);
	return (1);
}
