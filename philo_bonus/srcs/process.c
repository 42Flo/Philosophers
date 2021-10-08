/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:33:50 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/08 22:03:43 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			philo->index = i;
			break ;
		}
		i++;
	}
}

void	child_execution(t_philo *philo)
{
	philo->last_eat = get_timestamp();
	while (philo->data->state == running && philo->state != dead)
	{
		check_death(philo);
		if (eat(philo) != 0)
			break ;
		philo->state = sleeping;
		print_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking;
		print_status(philo, THINK);
	}
}

void	is_dead(t_philo *philo)
{
	philo->state = dead;
	philo->data->state = shutdown;
	print_status(philo, DEATH);
}

void	check_death(t_philo *philo)
{
	if (get_time_diff(philo->last_eat) > (size_t)philo->data->time_to_die)
		is_dead(philo);
}
