/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:54:46 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 11:46:35 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	argument_error(void)
{
	char	*message;

	message = "Error: Invalid argument\n";
	write(2, message, ft_strlen(message));
}

void	thread_error(void)
{
	char	*message;

	message = "Error: Thread creation failed\n";
	write(2, message, ft_strlen(message));
}

void	malloc_error(void)
{
	char	*message;

	message = "Error: Memory allocation failed\n";
	write(2, message, ft_strlen(message));
}

void	mutex_error(void)
{
	char	*message;

	message = "Error: Mutex initialization failed\n";
	write(2, message, ft_strlen(message));
}
