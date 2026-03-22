/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:22:22 by babe              #+#    #+#             */
/*   Updated: 2026/03/19 12:35:00 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define NO_EXIT -1

typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_must_eat;
}	t_params;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died_mutex;
	t_params		params;
	t_fork			*forks;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eat_count;
	long long		last_eat_time;
	pthread_mutex_t	eat_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
};

// error functions
void		error_exit(int code, void (*func)(void));
void		thread_error(void);
void		argument_error(void);
void		malloc_error(void);
void		mutex_error(void);

// routine functions
long long	time_in_ms(void);
void		*philo_routine(void *arg);

// thread functions
void		all_init(t_params *params, t_data *data, int argc, char **argv);
void		thread_create_join(t_data *data);
void		free_data(t_data *data);
void		cleanup_data(t_data *data);
void		cleanup(t_data *data);
void		cleanup_partial(t_data *data, int must);

// utils functions
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		param_check(int argc, char **argv);

#endif
