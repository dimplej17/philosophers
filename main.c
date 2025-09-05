// add 42 header

// for input error handling, intmax or longmax? time stuff has to be > 0, yeah? otherwise philos die instantly? 

// gcc -fsanitize=thread -g threads.c && ./a.out - add in makefile - to check something?? i forgot

#include "philo.h"

int main(int argc, char *argv[])
{
	// initialisation
    t_data input;
	int i;
	i = 0;
    input.start_time = get_absolute_time();
	// initial arg checks
    if (argc != 5 && argc != 6)
        return (valid_input(), 1);
    if (check_arg_if_int(argv[1]) == 1 || check_arg_if_int(argv[2]) == 1 || check_arg_if_int(argv[3]) == 1 || check_arg_if_int(argv[4]) == 1)
        return (valid_input(), 1);
    if (argc == 6)
    {
        if (check_arg_if_int(argv[1]) == 1)
            return (valid_input(), 1);
    }
    // input validity checks
    input.n_philo = ft_atol(argv[1]);
    if (input.n_philo < 1 || input.n_philo > 200) 
        return (valid_input(), 1);
    input.time_to_die = ft_atol(argv[2]);
    input.time_to_eat = ft_atol(argv[3]);
    input.time_to_sleep = ft_atol(argv[4]);
    if (arg_time_check(input.time_to_die) == 1 || arg_time_check(input.time_to_eat) == 1 || arg_time_check(input.time_to_sleep) == 1)
            return (valid_input(), 1);
    if (argc == 6)
    {
        input.must_eat = ft_atol(argv[5]);
        if (input.must_eat < 1 || input.must_eat > INT_MAX) // idk what the minimum (0 or 1?) & max for this is
            return (valid_input(), 1);
    }
    else
    	input.must_eat = -1;
    input.philo = malloc(sizeof(t_philo) * input.n_philo);
	if (!input.philo)
		return (1);
	
	input.stop = 0;
	if (pthread_mutex_init(&input.mutex_stop, NULL) != 0)
		return (free(input.philo), 1);
	input.mutex_fork = malloc(sizeof(pthread_mutex_t) * input.n_philo);
	if (!input.mutex_fork)
	{
		pthread_mutex_destroy(&input.mutex_stop);
		return (free(input.philo), 1);
	}
	i = 0;
	while (i < input.n_philo)
	{
		if (pthread_mutex_init(&input.mutex_fork[i], NULL) != 0)
		{
			pthread_mutex_destroy(&input.mutex_stop);
			return (free(input.philo), 1);
		}
		i++;
	}
	// handling input of 1 philo
    if (input.n_philo == 1)
		return (one_philo(&input), cleanup(&input), 0);

	// creating philos
	i = 0;
	while (i < input.n_philo - 1)
	{
		input.philo[i].id = i + 1;
		input.philo[i].left_fork = i;
		input.philo[i].right_fork = i + 1;
		input.philo[i].last_meal_eaten = input.start_time;
		input.philo[i].data = &input;
		i++;
	}
	input.philo[i].id = i + 1;
	input.philo[i].left_fork = i;
	input.philo[i].right_fork = 0;
	input.philo[i].last_meal_eaten = input.start_time;
    input.philo[i].data = &input;
	// creating a thread for each philo
	pthread_t threads[input.n_philo];
	i = 0;
	while (i < input.n_philo)
	{
		if (pthread_create(&threads[i], NULL, routine, &input.philo[i]) != 0)
			return (cleanup(&input), 1);
		i++;
	}
	// creating a monitor thread
	pthread_t monitor_thread;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &input) != 0)
		return (cleanup(&input), 1);
	// monitor thread join
	if (pthread_join(monitor_thread, NULL) != 0)
		return (cleanup(&input), 1);
	i = 0;
	while (i < input.n_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (cleanup(&input), 1);
		i++;
	}
	return (cleanup(&input), 1);
    return (0);
}
