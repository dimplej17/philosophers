// add 42 header

#include "philo.h"

void valid_input(void)
{
    printf("valid input: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"); // cross check if this is the write way to display it
}

int arg_time_check(long n)
{
    if (n > INT_MAX || n <= 0)
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

