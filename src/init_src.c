/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_src.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 11:52:05 by habe              #+#    #+#             */
/*   Updated: 2026/03/29 19:23:58 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	param_init(t_params *params, int argc, char **argv)
{
	param_check(argc, argv);
	params->num_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->count_must_eat = ft_atoi(argv[5]);
	else
		params->count_must_eat = -1;
	if (params->num_philos <= 0 || params->time_to_die <= 0
		|| params->time_to_eat <= 0 || params->time_to_sleep <= 0)
		error_exit(EXIT_FAILURE, argument_error);
	if (argc == 6 && params->count_must_eat <= 0)
		error_exit(EXIT_FAILURE, argument_error);
}

static void	alloc_data(t_params *params, t_data *data)
{
	data->forks = malloc(sizeof(t_fork) * params->num_philos);
	if (data->forks == NULL)
	{
		cleanup_data(data);
		error_exit(EXIT_FAILURE, malloc_error);
	}
	data->philos = malloc(sizeof(t_philo) * params->num_philos);
	if (data->philos == NULL)
	{
		cleanup_data(data);
		error_exit(EXIT_FAILURE, malloc_error);
	}
}

void	data_init(t_params *params, t_data *data)
{
	data->start_time = 0;
	data->someone_died = false;
	data->ate_enough_count = 0;
	data->forks = NULL;
	data->philos = NULL;
	data->params = *params;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		error_exit(EXIT_FAILURE, mutex_error);
	if (pthread_mutex_init(&data->died_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		error_exit(EXIT_FAILURE, mutex_error);
	}
	alloc_data(params, data);
}

void	philo_init(t_params *params, t_data *data)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % params->num_philos];
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		i++;
	}
}

void	mutex_init(t_params *params, t_data *data)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		{
			cleanup_partial(data, i);
			error_exit(EXIT_FAILURE, mutex_error);
		}
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL) != 0)
		{
			pthread_mutex_destroy(&data->forks[i].mutex);
			cleanup_partial(data, i);
			error_exit(EXIT_FAILURE, mutex_error);
		}
		i++;
	}
}
