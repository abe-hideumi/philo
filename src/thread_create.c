/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:37:30 by babe              #+#    #+#             */
/*   Updated: 2026/03/22 13:09:57 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	thread_create(t_data *data)
{
	int	count;

	count = 0;
	while (count < data->params.num_philos)
	{
		data->philos[count].last_eat_time = data->start_time;
		if (pthread_create(&data->philos[count].thread, NULL,
			philo_routine, &data->philos[count]) != 0)
		{
			free_data(data);
			error_exit(EXIT_FAILURE, thread_error);
		}
		count++;
	}
}

static void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			free_data(data);
			error_exit(EXIT_FAILURE, thread_error);
		}
		i++;
	}
}

void	thread_create_join(t_data *data)
{
	data->start_time = time_in_ms();
	thread_create(data);
	thread_join(data);
}
