// add 42 header

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef struct s_data
{
    long     n_philo;
    long     time_to_die;
    long     time_to_eat;
    long     time_to_sleep;
    long     must_eat;        // -1 if not provided
    long    start_time;      // when simulation began
    pthread_mutex_t *forks;  // array of mutexes
    pthread_mutex_t print;   // mutex for printing (to avoid mixed messages)
    t_philo philos*;
    int     stop;            // flag: someone died or all ate enough
}   t_data;

typedef struct s_philo
{
    long             id;
    long             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;


// helpers
void valid_input(void);
int arg_time_check(long n);
long	ft_atol(char *str);
int	check_arg_if_int(char *str);





#endif