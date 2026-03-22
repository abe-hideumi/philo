/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:54:46 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 12:35:38 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	argument_error(void)
{
	char	*msg;

	msg = "Error: Invalid argument\n";
	write(2, msg, ft_strlen(msg));
}

void	thread_error(void)
{
	char	*msg;

	msg = "Error: Thread creation failed\n";
	write(2, msg, ft_strlen(msg));
}

void	malloc_error(void)
{
	char	*msg;

	msg = "Error: Memory allocation failed\n";
	write(2, msg, ft_strlen(msg));
}

void	mutex_error(void)
{
	char	*msg;

	msg = "Error: Mutex initialization failed\n";
	write(2, msg, ft_strlen(msg));
}
