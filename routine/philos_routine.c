/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:30:29 by babe              #+#    #+#             */
/*   Updated: 2025/12/27 12:48:32 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_died(t_data *data)
{
	int result;

	pthread_mutex_lock(&data->died_mutex);
	
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->data)
	return (NULL);
}