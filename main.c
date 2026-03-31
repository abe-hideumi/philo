/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:31:21 by babe              #+#    #+#             */
/*   Updated: 2026/03/19 12:35:00 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;

	if (argc != 5 && argc != 6)
		error_exit(EXIT_FAILURE, argument_error);
	param_init(&params, argc, argv);
	data_init(&params, &data);
	philo_init(&params, &data);
	mutex_init(&params, &data);
	thread_create_join(&data);
	cleanup(&data);
	return (0);
}
