/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:50:39 by habe              #+#    #+#             */
/*   Updated: 2026/04/04 14:00:12 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	if (is_died(philo->data) == true)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_died(philo->data) == false)
	{
		if (printf("%lld %d %s\n", \
			time_in_ms() - philo->data->start_time, philo->id, status) < 0)
		{
			pthread_mutex_unlock(&philo->data->print_mutex);
			error_exit(EXIT_FAILURE, print_error);
		}
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

bool	is_died(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->died_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->died_mutex);
	return (result);
}

void	philo_think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, "is thinking");
	if (philo->data->params.num_philos % 2 == 0)
		return ;
	think_time = 2 * philo->data->params.time_to_eat
		- philo->data->params.time_to_sleep;
	if (think_time <= 0)
		think_time = 1;
	ft_sleep(think_time, philo->data);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = time_in_ms();
	pthread_mutex_unlock(&philo->eat_mutex);
	print_status(philo, "is eating");
	ft_sleep(philo->data->params.time_to_eat, philo->data);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (philo->data->params.count_must_eat != -1
		&& philo->eat_count == philo->data->params.count_must_eat)
	{
		pthread_mutex_lock(&philo->data->died_mutex);
		philo->data->ate_enough_count++;
		if (philo->data->ate_enough_count == philo->data->params.num_philos)
			philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->died_mutex);
	}
}

void	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->id == philo->data->params.num_philos)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(&first->mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&second->mutex);
	print_status(philo, "has taken a fork");
}
