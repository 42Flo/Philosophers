/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:18:34 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/20 15:14:38 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->sem->forks);
	print_status(philo, FORK);
	sem_wait(philo->sem->forks);
	print_status(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->sem->forks);
	sem_post(philo->sem->forks);
}

int	eat(t_philo *philo)
{
	if (philo->data->state == shutdown || philo->state == dead)
		return (-1);
	lock_forks(philo);
	philo->state = eating;
	sem_wait(philo->death);
	philo->last_eat = get_timestamp();
	sem_post(philo->death);
	print_status(philo, EAT);
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_counter++;
	unlock_forks(philo);
	return (0);
}
