/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:31:45 by babe              #+#    #+#             */
/*   Updated: 2026/03/28 11:58:06 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	all_init(t_params *params, t_data *data, int argc, char **argv)
{
	param_init(params, argc, argv);
	data_init(params, data);
	philo_init(params, data);
	mutex_init(params, data);
}
