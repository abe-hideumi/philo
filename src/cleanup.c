/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:05:00 by babe              #+#    #+#             */
/*   Updated: 2026/03/22 13:40:45 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	cleanup_data(t_data *data)
{
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died_mutex);
	free_data(data);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].eat_mutex);
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	cleanup_data(data);
}

void	cleanup_partial(t_data *data, int must)
{
	while (must > 0)
	{
		must--;
		pthread_mutex_destroy(&data->philos[must].eat_mutex);
		pthread_mutex_destroy(&data->forks[must].mutex);
	}
	cleanup_data(data);
}
