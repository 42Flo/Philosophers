/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:18:34 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/08 21:50:53 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->sem);
	print_status(philo, FORK);
	sem_wait(philo->sem);
	print_status(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->sem);
	sem_post(philo->sem);
}

int		eat(t_philo *philo)
{
	if (philo->data->state == shutdown || philo->state == dead)
		return (-1);
	lock_forks(philo);
	philo->state = eating;
	print_status(philo, EAT);
	philo->last_eat = get_timestamp();
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_counter++;
	unlock_forks(philo);
	return (0);
}
