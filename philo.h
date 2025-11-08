/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:22:22 by babe              #+#    #+#             */
/*   Updated: 2025/11/08 21:24:22 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fork
{
	int				id;
	int				is_taken;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	t_philo			*philos;
	t_fork			*forks;
}	t_table;

typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_must_eat;
}	t_params;

void	error_exit(int code);
void	param_init(t_params *params, int argc, char **argv);
int		ft_atoi(const char *str);

#endif