/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:49 by fregulie          #+#    #+#             */
/*   Updated: 2021/08/25 00:54:06 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include "libft/libft.h"

typedef struct	s_args
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_counter;
}				t_args;

typedef struct	s_philo
{
	t_args	a;
	pthread_mutex_t	*mutex;
	int	*forks;
	int	isdead;
	int	i;
}				t_philo;

#endif
