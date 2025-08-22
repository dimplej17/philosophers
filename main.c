// add 42 header

// for input error handling, intmax or longmax? time stuff has to be > 0, yeah? otherwise philos die instantly? 
// arguments: number_of_philosophers time_to_die time_to_eat
// time_to_sleep [number_of_times_each_philosopher_must_eat]
// should i also handle input given within quotes or nah?

#include "philo.h"

int main(int argc char *argv[])
{
    if (argc != 5 && argc != 6)
        return (valid_input(), 1);
    if (check_arg_if_int(argv[1]) == 1 || check_arg_if_int(argv[2]) == 1 || check_arg_if_int(argv[3]) == 1 || check_arg_if_int(argv[4]) == 1)
        return (valid_input(), 1);
    if (argc == 6)
    {
        if (check_arg_if_int(argv[1]) == 1)
            return (valid_input(), 1);
    }
    long n_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep
    long n_each_p_eat;
    n_philo = ft_atol(argv[1]);
    if (n_philo < 1 || n_philo > INT_MAX) // minimum how many philosophers?
        return (valid_input(), 1);
    time_to_die = ft_atol(argv[2]);
    time_to_eat = ft_atol(argv[3]);
    time_to_sleep = ft_atol(argv[4]);
    if (argc == 6)
    {
        n_each_p_eat = ft_atol(argv[5]);
        if (arg_time_check(time_to_die) == 1 || arg_time_check(time_to_eat) == 1 || arg_time_check(time_to_sleep) == 1 || arg_time_check(n_each_p_eat) == 1)
            return (valid_input(), 1);
    }
    else
    	n_each_p_eat = -1;

    return (0);
}
