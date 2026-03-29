/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:21:27 by habe              #+#    #+#             */
/*   Updated: 2026/03/29 14:30:45 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
