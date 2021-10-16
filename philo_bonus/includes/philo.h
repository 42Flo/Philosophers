/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:49 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/15 16:49:11 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

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
enum e_philo_state		{undef, eating, sleeping, thinking, dead};

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

typedef struct s_philo
{
	pid_t				pid;
	sem_t				*forks;
	sem_t				*print;
	int					index;
	int					eat_counter;
	long				last_eat;
	enum e_philo_state	state;
	t_data				*data;
}						t_philo;

/*
**(init.c)
*/

t_data	init_data(int ac, char **av);
t_philo	init_philo(t_data *data);

/*
**(print.c)
*/

void	print_index_color(t_philo *philo);
void	print_action_color(t_philo *philo, char *status);
void	print_status(t_philo *philo, char *status);

/*
**(process.c)
*/

void	create_process(t_philo *philo);
void	child_execution(t_philo *philo);
void	is_dead(t_philo *philo);
int		check_death(t_philo *philo);

/*
**(eat.c)
*/

void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		eat(t_philo *philo);

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
**(errors.c)
*/

void	int_min_max_error(char *err_target, long val);
char	**init_arg_errors_array(void);
void	check_arg_errors(int ac, char **av);
void	check_value_errors(t_data data);
void	exit_error(char *err_target, char *err);

#endif
