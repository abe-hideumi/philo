/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:30:29 by babe              #+#    #+#             */
/*   Updated: 2026/03/29 14:45:11 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philo_routine(t_philo *philo)
{
	long long	die_at;

	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	die_at = philo->data->start_time + philo->data->params.time_to_die;
	while (time_in_ms() < die_at)
		usleep(500);
	set_died(philo->data, philo);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->params.num_philos == 1)
		return (one_philo_routine(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	while (is_died(philo->data) == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_status(philo, "has taken a fork");
		philo_eat(philo);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		print_status(philo, "is sleeping");
		ft_sleep(philo->data->params.time_to_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
