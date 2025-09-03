// add 42 header

#include "philo.h"

void valid_input(void)
{
    printf("valid input: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"); // cross check if this is the write way to display it
}

int arg_time_check(long n)
{
    if (n > INT_MAX || n < 60)
        return (1);
    return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_arg_if_int(char *str)
{
	int	count;

	if (!str || !str[0])
		return (1);
	count = 0;
	if (str[0] == '-' || str[0] == '+')
		count++;
	if (!str[count])
		return (1);
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
			return (1);
		count++;
	}
	return (0);
}

long get_absolute_time(void)
{
	long ms;
	struct timeval absolute_time;
	gettimeofday(&absolute_time, NULL);
	ms = absolute_time.tv_sec * 1000L + absolute_time.tv_usec / 1000L;
	return (ms);
}

long get_current_time(t_data *data)
{
	return (get_absolute_time() - data->start_time);
}

void *routine_one_philo(void *data)
{
	t_philo *philo;
	philo  = (t_philo *)data;

	printf("%ld %d has taken a fork\n", get_absolute_time() - philo->data->start_time, philo->id);
    while (1)
    {
        if ((get_absolute_time() - philo->last_meal_eaten) >= philo->data->time_to_die)
        {
            printf("%ld %d died\n", get_absolute_time() - philo->data->start_time, philo->id);
            return (NULL);
        }
	}
    return (NULL);
}

void one_philo(t_data input)
{
	input.philo[0].id = 1;
	input.philo[0].left_fork = 0;
	input.philo[0].right_fork = -1;
	(void)input.philo[0].right_fork;
	input.philo[0].last_meal_eaten = input.start_time;
	input.philo[0].data = &input;
	pthread_t t_id1;
	if (pthread_create(&t_id1, NULL, routine_one_philo, &input.philo[0]) != 0)
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
		if ((get_current_time(philo->data) - philo->last_meal_eaten) >= philo->data->time_to_die)
        {
            printf("%ld %d died\n", get_current_time(philo->data) - philo->data->start_time, philo->id);
            return (NULL);
        }
	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]) != 0)
		return (NULL);
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
	if (pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]) != 0)	
		return (NULL);
	printf("%ld %d has taken a fork\n", get_current_time(philo->data), philo->id);
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