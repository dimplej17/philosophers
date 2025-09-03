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

void *routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	while (1)
	{
    if (philo->id % 2 != 0)
	{if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
		return (NULL);
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)	
	{
		if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]))	
			return (NULL);
		return (NULL);
	}
    printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
    }
    else if (philo->id % 2 == 0)
    {if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)
		return (NULL);
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)	
	{
		if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]))	
			return (NULL);
		return (NULL);
	}
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
}
	printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal_eaten = get_current_time(philo->data);
	if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]))	
		return (NULL);
	if (pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]))	
		return (NULL);
	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
	}
	return (NULL);
}

// simulation stopping - when a philo dies or when all philos have eaten must_eat number of times.
// when does a philo die? - 

// if (get_current_time() > philo->input.time_to_die)
// 	{printf("%ld %ld died\n", get_current_time(), philo->id);
// 	return (NULL);}
// 	if ((get_current_time() - input->philo[i].last_meal_eaten) > input.time_to_die)
// 	{printf("%ld %ld died\n", get_current_time(), input->philo->id); 
// 	return (NULL);}


// if ((get_current_time(philo->data) - philo->last_meal_eaten) >= philo->data->time_to_die)
//         {
//             printf("%ld %d died\n", get_current_time(philo->data), philo->id);
//             return (NULL);
//         }