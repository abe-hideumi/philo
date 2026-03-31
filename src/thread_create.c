/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:37:30 by babe              #+#    #+#             */
/*   Updated: 2026/03/29 19:30:08 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_threads_create(t_data *data)
{
	int	count;
	int	i;

	count = 0;
	while (count < data->params.num_philos)
	{
		if (pthread_create(&data->philos[count].thread, NULL,
				philo_routine, &data->philos[count]) != 0)
		{
			pthread_mutex_lock(&data->died_mutex);
			data->someone_died = true;
			pthread_mutex_unlock(&data->died_mutex);
			i = 0;
			while (i < count)
			{
				pthread_join(data->philos[i].thread, NULL);
				i++;
			}
			cleanup(data, data->params.num_philos);
			error_exit(EXIT_FAILURE, thread_error);
		}
		count++;
	}
}

static void	philo_threads_join(t_data *data)
{
	int	count;

	count = 0;
	while (count < data->params.num_philos)
	{
		if (pthread_join(data->philos[count].thread, NULL) != 0)
		{
			cleanup(data, data->params.num_philos);
			error_exit(EXIT_FAILURE, thread_error);
		}
		count++;
	}
}

static void	init_last_eat_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		data->philos[i].last_eat_time = data->start_time;
		i++;
	}
}

void	thread_create_join(t_data *data)
{
	data->start_time = time_in_ms();
	init_last_eat_time(data);
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
	{
		cleanup(data, data->params.num_philos);
		error_exit(EXIT_FAILURE, thread_error);
	}
	philo_threads_create(data);
	philo_threads_join(data);
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		cleanup(data, data->params.num_philos);
		error_exit(EXIT_FAILURE, thread_error);
	}
}
