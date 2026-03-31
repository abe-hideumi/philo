/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:05:00 by babe              #+#    #+#             */
/*   Updated: 2026/03/31 12:21:36 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_data(t_data *data)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
}

void	cleanup_data(t_data *data)
{
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died_mutex);
	free_data(data);
}

void	cleanup(t_data *data, int count)
{
	while (count > 0)
	{
		count--;
		pthread_mutex_destroy(&data->philos[count].eat_mutex);
		pthread_mutex_destroy(&data->forks[count].mutex);
	}
	cleanup_data(data);
}
