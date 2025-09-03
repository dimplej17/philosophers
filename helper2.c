// add 42 header

#include "philo.h"

long get_current_time(t_data *data)
{
	return (get_absolute_time() - data->start_time);
}
