/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:11:58 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 21:19:39 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->m_forks[philo->fork[RIGHT]]));
	print_status(philo, FORK);
	if (philo->data->nb_philo < 2)
	{
		pthread_mutex_unlock(&(philo->mutex->m_forks[philo->fork[RIGHT]]));
		return (false);
	}
	pthread_mutex_lock(&(philo->mutex->m_forks[philo->fork[LEFT]]));
	print_status(philo, FORK);
	return (true);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->mutex->m_forks[philo->fork[LEFT]]));
	pthread_mutex_unlock(&(philo->mutex->m_forks[philo->fork[RIGHT]]));
}

int	eat(t_philo *philo)
{
	if (check_pstate(philo, shutdown) || check_state(philo, dead))
		return (-1);
	if (!lock_forks(philo))
		return (-1);
	change_state(philo, eating);
	print_status(philo, EAT);
	pthread_mutex_lock(&(philo->m_death));
	philo->last_eat = get_timestamp();
	pthread_mutex_unlock(&philo->m_death);
	usleep(philo->data->time_to_eat * 1000);
	unlock_forks(philo);
	pthread_mutex_lock(&(philo->m_eat_count));
	philo->eat_counter++;
	pthread_mutex_unlock(&(philo->m_eat_count));
	return (0);
}
