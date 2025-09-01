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

long get_current_time(void)
{
	long ms;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000L + current_time.tv_usec / 1000L;
	return (ms);
}

void *routine(void *data)
{
	
	long ms;
	ms = get_current_time();
	int i;
	i = 1;
	while (threads[i])
	{
	if (ms > input.time_to_die)
	{printf("%ld %ld died\n", ms, input->philo->id);
	return ;}
	if ((ms - input->philo[i].last_meal_eaten) > input.time_to_die)
	{printf("%ld %ld died\n", ms, input->philo->id); 
	return ;}
	ms = get_current_time();
	printf("%ld %ld has taken a fork\n", ms, input->philo->id);
 	// lock mutex? - left fork?
	ms = get_current_time();
	printf("%ld %ld has taken a fork\n", ms, input->philo->id);
	// lock mutex? - right fork?
	ms = get_current_time();
	printf("%ld %ld is eating\n", ms, input->philo->id);
	usleep(input.time_to_eat * 1000);
	input->philo[i].last_meal_eaten = get_current_time();
 	ms = get_current_time();
	printf("%ld %ld is sleeping\n", ms, input->philo->id);
 	usleep(input.time_to_sleep * 1000);
	ms = get_current_time();
	printf("%ld %ld is thinking\n", ms, input->philo->id);
	i++;
	}
 	
	
	
}

// simulation stopping - when a philo dies or when all philos have eaten must_eat number of times.
// when does a philo die? - 