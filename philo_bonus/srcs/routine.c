/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 20:09:36 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/18 15:46:58 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	is_dead(t_philo *philo)
{
	philo->state = dead;
	print_status(philo, DEATH);
	kill(0, SIGINT);
}

int	check_death(t_philo *philo)
{
	if (get_time_diff(philo->last_eat) > (size_t)philo->data->time_to_die)
	{
		is_dead(philo);
		return (1);
	}
	return (0);
}

int	check_eat_counter(t_philo *philo)
{
	if (philo->data->max_eat != -1)
	{
		if (philo->eat_counter >= philo->data->max_eat)
		{
			philo->state = done_eating;
			return (1);
		}
	}
	return (0);
}

void	child_execution(t_philo *philo)
{
	philo->last_eat = get_timestamp();
	while (philo->state != dead)
	{
		eat(philo);
		if (check_eat_counter(philo) != 0)
			exit(0);
		philo->state = sleeping;
		print_status(philo, SLEEP);
		check_death(philo);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking;
		print_status(philo, THINK);
	}
}
