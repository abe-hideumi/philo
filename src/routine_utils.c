/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:50:39 by habe              #+#    #+#             */
/*   Updated: 2026/03/28 13:13:39 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	if (is_died(philo->data) == true)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_died(philo->data))
		printf("%lld %d %s\n", time_in_ms() - philo->data->start_time,
			philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	ft_sleep(philo->data->params.time_to_die, philo->data);
	set_died(philo->data, philo);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d died\n",
		time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	ft_sleep(long long ms, t_data *data)
{
	long long	end;

	end = time_in_ms() + ms;
	while (time_in_ms() < end)
	{
		if (is_died(data))
			return ;
		usleep(500);
	}
}

bool	is_died(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->died_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->died_mutex);
	return (result);
}

void	set_died(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->died_mutex);
	data->someone_died = true;
	pthread_mutex_unlock(&data->died_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d died\n", time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
