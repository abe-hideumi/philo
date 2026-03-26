/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:30:29 by babe              #+#    #+#             */
/*   Updated: 2026/03/24 16:34:16 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	is_died(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->died_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->died_mutex);
	return (result);
}

static void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_died(philo->data) == false)
		printf("%lld %d %s\n", time_in_ms() - philo->data->start_time,
			philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = time_in_ms();
	pthread_mutex_unlock(&philo->eat_mutex);
	print_status(philo, "is eating");
	usleep(philo->data->params.time_to_eat * 1000);
	philo->eat_count++;
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
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
		usleep(philo->data->params.time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
