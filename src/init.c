/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:31:45 by babe              #+#    #+#             */
/*   Updated: 2025/12/13 15:24:12 by babe             ###   ########.fr       */
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
		error_exit(-1);
	if (argc == 6 && params->count_must_eat <= 0)
		error_exit(-1);
}

static void	data_init( t_params *params, t_data *data)
{
	data->start_time = 0;
	data->someone_died = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->params = *params;
	data->forks = malloc(sizeof(t_fork) * params->num_philos);
	data->philos = malloc(sizeof(t_philo) * params->num_philos);
	if (data->forks == NULL || data->philos == NULL)
		error_exit(-1);
}

static void	mutex_init(t_params *params, t_data *data)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % params->num_philos];
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		pthread_mutex_init(&data->philos[i].eat_mutex, NULL);
		i++;
	}
}

void	all_init(t_params *params, t_data *data, int argc, char **argv)
{
	param_init(params, argc, argv);
	data_init(params, data);
	mutex_init(params, data);
}