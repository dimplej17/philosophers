// add 42 header

// for input error handling, intmax or longmax? time stuff has to be > 0, yeah? otherwise philos die instantly? 

// gcc -fsanitize=thread -g threads.c && ./a.out - add in makefile - to check something?? i forgot

#include "philo.h"

int main(int argc, char *argv[])
{
    t_input input;
	int count;
	count = 1;
    if (argc != 5 && argc != 6)
        return (valid_input(), 1);
    if (check_arg_if_int(argv[1]) == 1 || check_arg_if_int(argv[2]) == 1 || check_arg_if_int(argv[3]) == 1 || check_arg_if_int(argv[4]) == 1)
        return (valid_input(), 1);
    if (argc == 6)
    {
        if (check_arg_if_int(argv[1]) == 1)
            return (valid_input(), 1);
    }
    
    input.n_philo = ft_atol(argv[1]);
    if (input.n_philo < 1 || input.n_philo > 200) // minimum how many philosophers?
        return (valid_input(), 1);
    input.time_to_die = ft_atol(argv[2]);
    input.time_to_eat = ft_atol(argv[3]);
    input.time_to_sleep = ft_atol(argv[4]);
    if (arg_time_check(input.time_to_die) == 1 || arg_time_check(input.time_to_eat) == 1 || arg_time_check(input.time_to_sleep) == 1)
            return (valid_input(), 1);
    if (argc == 6)
    {
        input.must_eat = ft_atol(argv[5]);
        if (input.must_eat < 1 || input.must_eat > INT_MAX) // idk what the minimum & max for this is
            return (valid_input(), 1);
    }
    else
    	input.must_eat = -1;
    input->philo = malloc(sizeof(t_philo) * input->n_philo);
	while (count < input->n_philo - 1) // what if n_philo = 1?
	{
		input->philo[count].id = count;
		input->philo[count].left_fork = count;
		input->philo[count].right_fork = count + 1;
		count++;
	}
	input->philo[count].id = count;
	input->philo[count].left_fork = count;
	input->philo[count].right_fork = 0;
    // each philo must have a thread of their own
    pthread_t t_id1;
    if (pthread_create(&t_id1, NULL, routine, &input) != 0)
        {
            free(input->philo);
            return (1);
        }



    free(input->philo);
    return (0);


}
