/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:37:30 by babe              #+#    #+#             */
/*   Updated: 2025/12/14 17:44:15 by babe             ###   ########.fr       */
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
		{
			error_exit(-1);
		}
		i++;
	}
	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			error_exit(-1);
		i++;
	}
}