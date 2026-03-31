/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:30:29 by babe              #+#    #+#             */
/*   Updated: 2026/03/29 19:41:48 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	ft_sleep(philo->data->params.time_to_die, philo->data);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->params.num_philos == 1)
	{
		one_philo_routine(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->params.time_to_eat, philo->data);
	while (is_died(philo->data) == false)
	{
		take_forks(philo);
		philo_eat(philo);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		print_status(philo, "is sleeping");
		ft_sleep(philo->data->params.time_to_sleep, philo->data);
		philo_think(philo);
	}
	return (NULL);
}
