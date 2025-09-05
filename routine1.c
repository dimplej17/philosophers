// add 42 header

#include "philo.h"

void *routine_one_philo(void *data)
{
	t_philo *philo;
	philo  = (t_philo *)data;

	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
    while (1)
    {
        if ((get_absolute_time() - philo->last_meal_eaten) >= philo->data->time_to_die)
        {
            printf("%ld %d died\n", get_current_time(philo->data), philo->id);
            return (NULL);
        }
	}
    return (NULL);
}

void one_philo(t_data *input)
{
	input->philo[0].id = 1;
	input->philo[0].left_fork = 0;
	input->philo[0].right_fork = -1;
	(void)input->philo[0].right_fork;
	input->philo[0].last_meal_eaten = input->start_time;
	input->philo[0].data = input;
	pthread_t t_id1;
	if (pthread_create(&t_id1, NULL, routine_one_philo, &input->philo[0]) != 0)
		return ;
	if (pthread_join(t_id1, NULL) != 0)
		return ;
}

int should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	int stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	return (stop);
}

int take_forks(t_philo *philo)
{
	int first_fork, second_fork;
	
	// Simple solution: always take the lower-numbered fork first globally
	// This prevents circular wait completely
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
	
	// Take first fork
	if (pthread_mutex_lock(&philo->data->mutex_fork[first_fork]) != 0)
		return (0);
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	
	// Check if we should stop before taking second fork
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	
	// Take second fork
	if (pthread_mutex_lock(&philo->data->mutex_fork[second_fork]) != 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
		return (0);
	}
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	return (1);
}

void eat(t_philo *philo)
{
    printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
    usleep(philo->data->time_to_eat * 1000);
    
    // Update meal time AFTER eating finishes
    pthread_mutex_lock(&philo->data->mutex_stop);
    philo->last_meal_eaten = get_absolute_time();
	philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->mutex_stop);
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void sleep_phase(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void think_phase(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
	// Add small delay to prevent excessive CPU usage
	usleep(1000);
}

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	// Stagger even-numbered philosophers to reduce initial contention
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500); // Half eating time delay
	
	while (!should_stop(philo))
	{
		if (!take_forks(philo))
			break;
			
		eat(philo);
		drop_forks(philo);
		
		if (should_stop(philo))
			break;
			
		sleep_phase(philo);
		
		if (should_stop(philo))
			break;
			
		think_phase(philo);
	}
	return (NULL);
}


// int should_stop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->mutex_stop);
// 	int stop = philo->data->stop;
// 	pthread_mutex_unlock(&philo->data->mutex_stop);
// 	return (stop);
// }

// int take_forks(t_philo *philo)
// {
// 	int first_fork, second_fork;
	
// 	// Simple solution: always take the lower-numbered fork first globally
// 	// This prevents circular wait completely
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
	
// 	// Take first fork
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[first_fork]) != 0)
// 		return (0);
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	
// 	// Check if we should stop before taking second fork
// 	if (should_stop(philo))
// 	{
// 		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
// 		return (0);
// 	}
	
// 	// Take second fork
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[second_fork]) != 0)
// 	{
// 		pthread_mutex_unlock(&philo->data->mutex_fork[first_fork]);
// 		return (0);
// 	}
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// 	return (1);
// }

// void eat(t_philo *philo)
// {
// 	printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
	
// 	pthread_mutex_lock(&philo->data->mutex_stop);
// 	philo->last_meal_eaten = get_absolute_time();
// 	pthread_mutex_unlock(&philo->data->mutex_stop);
	
// 	usleep(philo->data->time_to_eat * 1000);
// }

// void drop_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
// 	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
// }

// void sleep_phase(t_philo *philo)
// {
// 	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
// 	usleep(philo->data->time_to_sleep * 1000);
// }

// void think_phase(t_philo *philo)
// {
// 	printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
// 	// Add small delay to prevent excessive CPU usage
// 	usleep(1000);
// }

// void *routine(void *data)
// {
// 	t_philo *philo = (t_philo *)data;
	
// 	// Stagger even-numbered philosophers to reduce initial contention
// 	if (philo->id % 2 == 0)
// 		usleep(philo->data->time_to_eat * 500); // Half eating time delay
	
// 	while (!should_stop(philo))
// 	{
// 		if (!take_forks(philo))
// 			break;
			
// 		eat(philo);
// 		drop_forks(philo);
		
// 		if (should_stop(philo))
// 			break;
			
// 		sleep_phase(philo);
		
// 		if (should_stop(philo))
// 			break;
			
// 		think_phase(philo);
// 	}
// 	return (NULL);
// }

// void *routine(void *data)
// {
// 	t_philo *philo;
// 	philo = (t_philo *)data;

// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->data->mutex_stop);
//     if (philo->data->stop)
//     {
//         pthread_mutex_unlock(&philo->data->mutex_stop);
//         break; // exit the thread
//     }
//     pthread_mutex_unlock(&philo->data->mutex_stop);
// 	if (philo->id == philo->data->n_philo) // Last philosopher
// {
//     // Take lower-numbered fork first (fork 0), then higher (fork 4)
//     if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)
//         return (NULL);
//     printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
    
//     if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
//     {
//         pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
//         return (NULL);
//     }
//     printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// }
//     else if (philo->id % 2 != 0)
// 	{if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
// 		return (NULL);
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)	
// 	{
// 		if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]))	
// 			return (NULL);
// 		return (NULL);
// 	}
//     printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
//     }
//     else if (philo->id % 2 == 0)
//     {if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)
// 		return (NULL);
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// 	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)	
// 	{
// 		if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]))	
// 			return (NULL);
// 		return (NULL);
// 	}
// 	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
// }
// 	printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
// // Protect the update with mutex
// pthread_mutex_lock(&philo->data->mutex_stop);
// philo->last_meal_eaten = get_absolute_time();
// pthread_mutex_unlock(&philo->data->mutex_stop);
// usleep(philo->data->time_to_eat * 1000);
// 	if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]))	
// 		return (NULL);
// 	if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]))	
// 		return (NULL);
// 	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
// 	usleep(philo->data->time_to_sleep * 1000);
// 	pthread_mutex_lock(&philo->data->mutex_stop);
//         if (philo->data->stop) {
//             pthread_mutex_unlock(&philo->data->mutex_stop);
//             break;
//         }
//         pthread_mutex_unlock(&philo->data->mutex_stop);
// 	printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
// 	}
// 	return (NULL);
// }

// simulation stopping - when a philo dies or when all philos have eaten must_eat number of times.
