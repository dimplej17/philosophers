// add 42 header

#include "philo.h"

int should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	int stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	return (stop);
}

int take_forks(t_philo *philo)
{
	int first_fork;
	int second_fork;
	
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
		if (should_stop(philo))
		return (0);
	if (pthread_mutex_lock(&philo->data->mutex_fork[first_fork]) != 0)
		return (0);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
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
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	return (1);
}

// int take_forks(t_philo *philo)
// {
// 	int first_fork;
// 	int second_fork;
	
// 	if (philo->left_fork < philo->right_fork)
// 	{
// 		first_fork = philo->left_fork;
// 		second_fork = philo->right_fork;
// 	}
// 	else
// 	{
// 		first_fork = philo->right_fork;
// 		second_fork = philo->left_fork;
// 	}
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[first_fork]) != 0)
// 		return (0);
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// 	if (should_stop(philo))
// 	{
// 		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
// 		return (0);
// 	}
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[second_fork]) != 0)
// 	{
// 		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
// 		return (0);
// 	}
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// 	return (1);
// }

void eat(t_philo *philo)
{
	if (should_stop(philo))
		return;
		
	printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	
	// Update meal time AFTER eating finishes
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (!philo->data->stop)  // Double-check inside mutex
	{
		philo->last_meal_eaten = get_absolute_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->data->mutex_stop);
}

// void eat(t_philo *philo)
// {
//     printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
//     usleep(philo->data->time_to_eat * 1000);
    
//     // Update meal time AFTER eating finishes
//     pthread_mutex_lock(&philo->data->mutex_stop);
//     philo->last_meal_eaten = get_absolute_time();
// 	philo->meals_eaten++;
//     pthread_mutex_unlock(&philo->data->mutex_stop);
// }

void drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void sleep_phase(t_philo *philo)
{
	if (should_stop(philo))
		return;
		
	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

// void sleep_phase(t_philo *philo)
// {
// 	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
// 	usleep(philo->data->time_to_sleep * 1000);
// }
