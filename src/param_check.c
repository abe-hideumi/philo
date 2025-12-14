/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:24:14 by babe              #+#    #+#             */
/*   Updated: 2025/12/13 15:32:22 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	param_length(char *str)
{
	int	len;
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	len = 0;
	while (str[i] != '\0')
	{
		len++;
		i++;
	}
	if (len > 10)
		error_exit(-1);
}

void	param_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '\0')
			error_exit(-1);
		if (argv[i][0] == '+')
			j++;
		if (argv[i][0] == '-')
			error_exit(-1);
		param_length(argv[i]);
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_exit(-1);
			j++;
		}
		i++;
	}
}