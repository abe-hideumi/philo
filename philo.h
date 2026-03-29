/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:22:22 by babe              #+#    #+#             */
/*   Updated: 2026/03/29 14:22:29 by habe             ###   ########.fr       */
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
	bool			someone_died;
	int				ate_enough_count;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died_mutex;
	pthread_t		monitor_thread;
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

// time functions
long long	time_in_ms(void);
void		ft_sleep(long long ms, t_data *data);

// action functions
bool		is_died(t_data *data);
void		set_died(t_data *data, t_philo *philo);
void		print_status(t_philo *philo, char *status);
void		philo_eat(t_philo *philo);

// routine functions
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);

// init functions
void		param_init(t_params *params, int argc, char **argv);
void		data_init(t_params *params, t_data *data);
void		philo_init(t_params *params, t_data *data);
void		mutex_init(t_params *params, t_data *data);

// thread functions
void		thread_create_join(t_data *data);

// cleanup functions
void		free_data(t_data *data);
void		cleanup_data(t_data *data);
void		cleanup(t_data *data);
void		cleanup_partial(t_data *data, int must);

// utils functions
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		param_check(int argc, char **argv);

#endif
