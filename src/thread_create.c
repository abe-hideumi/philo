/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:37:30 by babe              #+#    #+#             */
/*   Updated: 2025/12/14 17:01:06 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <string.h>

static long long	time_in_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	long long	current_time;
	long long	elapsed_time;

	philo = (t_philo *)arg;
	current_time = time_in_ms();
	elapsed_time = current_time - philo->data->start_time;

	printf("=== Debug Info for Philosopher %d ===\n", philo->id);
	printf("Thread successfully created\n");
	printf("philo_routine called!\n");
	printf("Start time: %lld ms\n", philo->data->start_time);
	printf("Current time: %lld ms\n", current_time);
	printf("Elapsed time: %lld ms\n", elapsed_time);
	printf("=====================================\n\n");
	return (NULL);
}

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
				error_exit(-1);
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