/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:33:50 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/15 17:33:46 by fregulie         ###   ########.fr       */
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

void	is_dead(t_philo *philo)
{
	philo->state = dead;
	print_status(philo, DEATH);
	//sem_wait(philo->print);
	kill(0, SIGINT);
}

int		check_death(t_philo *philo)
{
	if (get_time_diff(philo->last_eat) > (size_t)philo->data->time_to_die)
	{
		is_dead(philo);
		return (1);
	}
	return (0);
}

void	child_execution(t_philo *philo)
{
	philo->last_eat = get_timestamp();
	while (philo->state != dead)
	{
		eat(philo);
		philo->state = sleeping;
		print_status(philo, SLEEP);
		check_death(philo);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking;
		print_status(philo, THINK);
	}
}
