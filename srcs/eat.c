/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:11:58 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/27 18:58:05 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->forks[philo->fork[LEFT]]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->mutex->forks[philo->fork[RIGHT]]);
	print_status(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->mutex->forks[philo->fork[RIGHT]]);
}

int		eat(t_philo *philo)
{
	lock_forks(philo);
	//pthread_mutex_lock(&philo->mutex->death);
	philo->state = eating; //
	print_status(philo, EAT);
	philo->last_eat = get_timestamp();
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_counter++;
	//pthread_mutex_unlock(&philo->mutex->death);
	unlock_forks(philo);
	return (0);
}
