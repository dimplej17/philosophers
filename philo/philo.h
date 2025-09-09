/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:30 by djanardh          #+#    #+#             */
/*   Updated: 2025/09/09 02:46:42 by djanardh         ###   ########.fr       */
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
	long			must_eat;
	long			start_time;
	pthread_t		*threads;
	pthread_mutex_t	*mutex_fork;
	int				stop;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
	pthread_mutex_t	ready_mutex;
	int				threads_ready;
}					t_data;

// main
int					init_ready_mutex(t_data *input);
int					init_mutexes(t_data *input);
int					create_philos(t_data *input);

// input parser
void				valid_input(void);
int					arg_time_check(long n);
int					check_arg_if_int(char *str);
int					validate_args(int argc, char *argv[]);
int					atol_args(t_data *input, int argc, char *argv[]);

// helper1
long				ft_atol(char *str);
long				get_absolute_time(void);
long				get_current_time(t_data *data);
void				smart_sleep(long duration, t_philo *philo);

// helper2
int					check_all_eaten_enough(t_data *input);
void				cleanup(t_data *data);
void				del_meal_mut(t_data *data);
int					create_thread_philo(t_data *input);

// helper 3
int					ft_philo_threads_join(t_data *input);
void				safe_print(t_data *data, int id, char *msg);
int					check_stop_status(t_data *input);
int					handle_death(t_data *input, int i);

// one philo case
void				one_philo(t_data *input);
void				*routine_one_philo(void *data);

// threads ready check
void				wait_all_ready(t_data *data);
void				mark_thread_ready(t_data *data);

// routine_thread
void				*routine(void *data);

// monitor routine
int					check_philosopher_death(t_data *input, int i);
int					monitor_all_philosophers(t_data *input);
int					check_eating_completion(t_data *input);
void				*monitor_routine(void *data);

// routine_actions
int					should_stop(t_philo *philo);
void				eat(t_philo *philo);
void				drop_forks(t_philo *philo);
void				sleep_phase(t_philo *philo);
void				think_phase(t_philo *philo);

// routine_forks
int					take_forks(t_philo *philo);

#endif