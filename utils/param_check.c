/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:24:14 by babe              #+#    #+#             */
/*   Updated: 2026/03/17 12:16:32 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	check_arg(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str[i] == '\0' || str[i] == '-')
		error_exit(EXIT_FAILURE, argument_error);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		error_exit(EXIT_FAILURE, argument_error);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			error_exit(EXIT_FAILURE, argument_error);
		len++;
		i++;
	}
	if (len > 10)
		error_exit(EXIT_FAILURE, argument_error);
}

void	param_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		check_arg(argv[i]);
		i++;
	}
}
