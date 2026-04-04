/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:24:14 by babe              #+#    #+#             */
/*   Updated: 2026/03/31 12:04:02 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_arg(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str[i] == '\0' || str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		len++;
		i++;
	}
	if (len > 10)
		return (1);
	return (0);
}

void	param_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_arg(argv[i]) != 0)
			error_exit(EXIT_FAILURE, argument_error);
		i++;
	}
}
