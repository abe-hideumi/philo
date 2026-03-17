/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:37:30 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 11:47:54 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thread_create(t_data *data)
{
	int	i;

	data->start_time = time_in_ms();
	i = 0;
	while (i < data->params.num_philos)
	{
		data->philos[i].last_eat_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			error_exit(EXIT_FAILURE, thread_error);
		i++;
	}
	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			error_exit(EXIT_FAILURE, thread_error);
		i++;
	}
}
