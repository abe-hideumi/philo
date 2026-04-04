/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:21:27 by habe              #+#    #+#             */
/*   Updated: 2026/04/04 13:59:59 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_died(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->died_mutex);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->died_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	data->someone_died = true;
	pthread_mutex_unlock(&data->died_mutex);
	if (printf("%lld %d died\n", \
			time_in_ms() - data->start_time, philo->id) < 0)
	{
		pthread_mutex_unlock(&data->print_mutex);
		error_exit(EXIT_FAILURE, print_error);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (is_died(data) == false)
	{
		i = 0;
		while (i < data->params.num_philos)
		{
			pthread_mutex_lock(&data->philos[i].eat_mutex);
			if (time_in_ms() - data->philos[i].last_eat_time
				>= (long long)data->params.time_to_die)
			{
				pthread_mutex_unlock(&data->philos[i].eat_mutex);
				set_died(data, &data->philos[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
