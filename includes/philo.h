/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:49 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/24 21:08:09 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define LEFT 0
# define RIGHT 1

typedef struct	s_data
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_eat;
}				t_data;

typedef struct	s_mutex
{
	pthread_mutex_t	*forks;
}				t_mutex;

typedef struct	s_philo
{
	t_data	*data;
	t_mutex	*mutex;
	int		fork[2];
}				t_philo;

/*
**(init.c)
*/

t_data	init_data(int ac, char **av);
t_mutex	init_mutex(int nb_philo);
t_philo	*init_philo(t_data data, t_mutex mutex);
void	init_forks(t_philo *philo, int i);

/*
**(threads.c)
*/

int	create_threads(t_philo *philo, pthread_t *philo_t);
int	join_threads(t_philo *philo, pthread_t *philo_t);
int	start_threads(t_philo *philo);

/*
**(routine.c)
*/

void	*routine(void *philo);

/*
**(tools.c)
*/

int	ft_isdigit(int c);
int	ft_atoi(const char *str);



#endif
