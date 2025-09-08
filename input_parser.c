/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:59:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 21:38:56 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	valid_input(void)
{
	printf("valid input: number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	arg_time_check(long n)
{
	if (n > INT_MAX || n < 60)
		return (1);
	return (0);
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

int	validate_args(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (valid_input(), 1);
	if (check_arg_if_int(argv[1]) == 1 || check_arg_if_int(argv[2]) == 1
		|| check_arg_if_int(argv[3]) == 1 || check_arg_if_int(argv[4]) == 1)
		return (valid_input(), 1);
	if (argc == 6)
	{
		if (check_arg_if_int(argv[5]) == 1)
			return (valid_input(), 1);
	}
	return (0);
}

int	atol_args(t_data *input, int argc, char *argv[])
{
	input->n_philo = ft_atol(argv[1]);
	if (input->n_philo < 1 || input->n_philo > 200)
		return (valid_input(), 1);
	input->time_to_die = ft_atol(argv[2]);
	input->time_to_eat = ft_atol(argv[3]);
	input->time_to_sleep = ft_atol(argv[4]);
	if (arg_time_check(input->time_to_die) == 1
		|| arg_time_check(input->time_to_eat) == 1
		|| arg_time_check(input->time_to_sleep) == 1)
		return (valid_input(), 1);
	if (argc == 6)
	{
		input->must_eat = ft_atol(argv[5]);
		if (input->must_eat < 1 || input->must_eat > INT_MAX)
			return (valid_input(), 1);
	}
	else
		input->must_eat = -1;
	return (0);
}
