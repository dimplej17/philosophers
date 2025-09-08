/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:59:39 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 22:33:59 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_absolute_time(void)
{
	long			ms;
	struct timeval	absolute_time;

	gettimeofday(&absolute_time, NULL);
	ms = absolute_time.tv_sec * 1000L + absolute_time.tv_usec / 1000L;
	return (ms);
}

long	get_current_time(t_data *data)
{
	return (get_absolute_time() - data->start_time);
}

void	smart_sleep(long duration, t_philo *philo)
{
	long	start_of_sleep;

	start_of_sleep = get_absolute_time();
	while (!should_stop(philo))
	{
		if (get_absolute_time() - start_of_sleep >= duration)
			break ;
		usleep(100);
	}
}
