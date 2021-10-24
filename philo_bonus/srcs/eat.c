/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:18:34 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 18:52:09 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->sem->s_forks);
	print_status(philo, FORK);
	sem_wait(philo->sem->s_forks);
	print_status(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->sem->s_forks);
	sem_post(philo->sem->s_forks);
}

int	eat(t_philo *philo)
{
	if (check_pstate(philo, shutdown) || check_state(philo, dead))
		return (-1);
	lock_forks(philo);
	change_state(philo, eating);
	sem_wait(philo->s_death);
	philo->last_eat = get_timestamp();
	sem_post(philo->s_death);
	print_status(philo, EAT);
	usleep(philo->data->time_to_eat * 1000);
	unlock_forks(philo);
	philo->eat_counter++;
	return (0);
}
