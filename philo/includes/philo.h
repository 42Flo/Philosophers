/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:49 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 16:57:54 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

# define ARG1 "number_of_philosophers"
# define ARG2 "time_to_die"
# define ARG3 "time_to_eat"
# define ARG4 "time_to_sleep"
# define ARG5 "max_eat"

# define LEFT 0
# define RIGHT 1

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"

enum e_program_state	{running, shutdown};
enum e_philo_state		{undef, eating, sleeping, thinking, dead, done_eating};

typedef struct s_data
{
	long					nb_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					max_eat;
	size_t					first_time;
	enum e_program_state	state;
}							t_data;

typedef struct s_mutex
{
	pthread_mutex_t		m_print;
	pthread_mutex_t		m_pstate;
	pthread_mutex_t		*m_forks;
}						t_mutex;

typedef struct s_philo
{
	pthread_t			tid;
	bool				started;
	int					index;
	int					fork[2];
	int					eat_counter;
	long				last_eat;
	enum e_philo_state	state;
	t_data				*data;
	t_mutex				*mutex;
	pthread_mutex_t		m_eat_count;
	pthread_mutex_t		m_death;
	pthread_mutex_t		m_state;
	pthread_mutex_t		m_start;
}						t_philo;

/*
**(init.c)
*/

t_data	init_data(int ac, char **av);
t_mutex	init_mutex(int nb_philo);
t_philo	*init_philo(t_data *data, t_mutex *mutex);
void	init_forks(t_philo *philo, int i);

/*
**(threads.c)
*/

int		create_threads(t_philo *philo);
int		join_threads(t_philo *philo);
int		start_threads(t_philo *philo);

/*
**(start.c)
*/

void	init_start_val(t_philo *philo);
bool	check_start_val(t_philo *philo);

/*
**(routine.c)
*/

void	*routine(void *philo);
void	is_dead(t_philo *philo);
void	check_end(t_philo *philo);
bool	check_eat_counter(t_philo *philo);

/*
**(eat.c)
*/

bool	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		eat(t_philo *philo);

/*
**(print.c)
*/

void	print_index_color(t_philo *philo);
void	print_action_color(t_philo *philo, char *status);
void	print_status(t_philo *philo, char *status);

/*
**(state.c)
*/

void	change_state(t_philo *philo, int state);
bool	check_state(t_philo *philo, enum e_philo_state state);
void	change_pstate(t_philo *philo, int pstate);
bool	check_pstate(t_philo *philo, enum e_program_state state);

/*
**(tools.c)
*/

int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);

/*
**(time.c)
*/

size_t	get_time_diff(size_t last_eat);
size_t	get_timestamp(void);

/*
**(end_free.c)
*/

int		destroy_shared_mutexes(t_philo *philo);
void	free_philo(t_philo *philo);
void	free_2d(void **arr, int size);

/*
**(errors.c)
*/

void	int_min_max_error(char *err_target, long val);
char	**init_arg_errors_array(void);
void	check_arg_errors(int ac, char **av);
void	check_value_errors(t_data data);
void	exit_error(char *err_target, char *err);

#endif
