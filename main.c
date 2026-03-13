/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:31:21 by babe              #+#    #+#             */
/*   Updated: 2026/03/13 12:33:56 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1);
	}
	all_init(&params, &data, argc, argv);
	thread_create(&data);
	cleanup(&data);
	return (0);
}