/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:31:21 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 11:45:22 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;

	if (argc != 5 && argc != 6)
		error_exit(EXIT_FAILURE, argument_error);
	all_init(&params, &data, argc, argv);
	thread_create(&data);
	cleanup(&data);
	return (0);
}
