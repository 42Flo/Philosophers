/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:21:25 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/08 18:42:38 by fregulie         ###   ########.fr       */
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

void	check_death(t_philo *philo)
{
	int	i;

	while (philo->data->state == running)
	{
		i = 0;
		while (i < philo->data->nb_philo && philo[i].last_eat != -1
			&& philo->data->state == running)
		{
			if (get_time_diff(philo[i].last_eat)
				> (size_t)philo->data->time_to_die)
				is_dead(&philo[i]);
			i++;
		}
	}
}
