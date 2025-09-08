/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:30 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/08 18:24:58 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h> // usleep()

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_eaten;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long			n_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long must_eat;   // -1 if not provided
	long start_time; // when simulation began
	pthread_t		*threads;
	pthread_mutex_t	*mutex_fork;
	int stop; // flag: someone died or all ate enough
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}					t_data;

// main
int					validate_args(int argc, char *argv[]);
int					atol_args(t_data *input, int argc, char *argv[]);
int					init_mutexes(t_data *input);
int					create_philos(t_data *input);

// helper1
void				valid_input(void);
int					arg_time_check(long n);
long				ft_atol(char *str);
int					check_arg_if_int(char *str);
long				get_absolute_time(void);

// helper2
long				get_current_time(t_data *data);
int					check_all_eaten_enough(t_data *input);
void				cleanup(t_data *data);
void				destroy_meal_mutex(t_data *data);
int					create_thread_philo(t_data *input);

// helper 3
int					ft_philo_threads_join(t_data *input);
void				safe_print(t_data *data, int id, char *msg);
int					check_stop_status(t_data *input);
long				get_time_since_meal(t_data *input, int i);
int					handle_death(t_data *input, int i);

// routine1
void				one_philo(t_data *input);
void				*routine_one_philo(void *data);
void				think_phase(t_philo *philo);
void				*routine(void *data);

// monitor routine
int					check_philosopher_death(t_data *input, int i);
int					monitor_all_philosophers(t_data *input);
int					handle_all_eaten(t_data *input);
int					check_eating_completion(t_data *input);
void				*monitor_routine(void *data);

// routine1 helpers
int					should_stop(t_philo *philo);
int					take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				drop_forks(t_philo *philo);
void				sleep_phase(t_philo *philo);

#endif