/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:50:39 by habe              #+#    #+#             */
/*   Updated: 2026/03/28 18:18:09 by habe             ###   ########.fr       */
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
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return ;
	}
	data->someone_died = true;
	pthread_mutex_unlock(&data->died_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d died\n", time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
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
	if (philo->eat_count == philo->data->params.count_must_eat)
	{
		pthread_mutex_lock(&philo->data->died_mutex);
		philo->data->ate_enough_count++;
		if (philo->data->ate_enough_count == philo->data->params.num_philos)
			philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->died_mutex);
	}
}
