// add 42 header

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> // usleep()

typedef struct s_philo
{
	int id;
	int left_fork;
    int right_fork;
	long last_meal_eaten;
    int     stop; // flag: someone died or all ate enough
	struct s_data *data;
}	t_philo;

typedef struct s_data
{
    long     n_philo;
    long     time_to_die;
    long     time_to_eat;
    long     time_to_sleep;
    long     must_eat;        // -1 if not provided
    long    start_time;      // when simulation began
    pthread_mutex_t *mutex_fork;
    t_philo *philo;
}   t_data;

// helpers
void valid_input(void);
int arg_time_check(long n);
long	ft_atol(char *str);
int	check_arg_if_int(char *str);
long get_current_time(void);
void one_philo(t_data input);
void *routine_one_philo(void *data);
void *routine(void *data);





#endif