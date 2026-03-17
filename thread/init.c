/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:31:45 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 11:47:40 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	param_init(t_params *params, int argc, char **argv)
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

static void	data_init(t_params *params, t_data *data)
{
	data->start_time = 0;
	data->someone_died = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		error_exit(EXIT_FAILURE, mutex_error);
	if (pthread_mutex_init(&data->died_mutex, NULL))
		error_exit(EXIT_FAILURE, mutex_error);
	data->params = *params;
	data->forks = malloc(sizeof(t_fork) * params->num_philos);
	if (data->forks == NULL)
		error_exit(EXIT_FAILURE, malloc_error);
	data->philos = malloc(sizeof(t_philo) * params->num_philos);
	if (data->philos == NULL)
	{
		free(data->forks);
		error_exit(EXIT_FAILURE, malloc_error);
	}
}

static void	mutex_init(t_params *params, t_data *data)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			error_exit(EXIT_FAILURE, mutex_error);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % params->num_philos];
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL))
			error_exit(EXIT_FAILURE, mutex_error);
		i++;
	}
}

void	all_init(t_params *params, t_data *data, int argc, char **argv)
{
	param_init(params, argc, argv);
	data_init(params, data);
	mutex_init(params, data);
}
