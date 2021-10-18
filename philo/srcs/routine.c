/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:21:25 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/18 13:40:28 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	philo->last_eat = get_timestamp();
	while (philo->data->state == running && philo->state != dead)
	{
		if (philo->index % 2 == 0 || philo->state != undef)
			if (eat(philo) != 0)
				break ;
		if (check_eat_counter(philo) != 0)
			break ;
		philo->state = sleeping;
		print_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking;
		print_status(philo, THINK);
	}
	return (NULL);
}

void	is_dead(t_philo *philo)
{
	philo->state = dead;
	philo->data->state = shutdown;
	print_status(philo, DEATH);
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

void	check_death(t_philo *philo)
{
	int	i;
	int	all_done_eating;

	usleep(philo->data->time_to_die * 1000);
	while (philo->data->state == running)
	{
		i = 0;
		all_done_eating = 1;
		while (i < philo->data->nb_philo && philo->data->state == running)
		{
			if (philo[i].state != done_eating)
				all_done_eating = 0;
			if (philo[i].state != done_eating
				&& get_time_diff(philo[i].last_eat)
				> (size_t)philo->data->time_to_die)
				is_dead(&philo[i]);
			i++;
		}
		if (all_done_eating != 0 && philo[i].last_eat != -1)
			philo->data->state = shutdown;
	}
}
