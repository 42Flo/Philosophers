/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:49 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/16 03:32:53 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
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
}				t_data;

typedef struct	s_mutex
{
	pthread_mutex_t	*forks;
}				t_mutex;

typedef struct	s_philo
{
	t_data	*data;
	int		fork[2];
}				t_philo;

/*
**(tools.c)
*/

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif
