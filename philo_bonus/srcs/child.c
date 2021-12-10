/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 20:09:36 by fregulie          #+#    #+#             */
/*   Updated: 2021/12/10 15:29:59 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	is_dead(t_philo *philo)
{
	sem_wait(philo->sem->s_print);
	change_state(philo, dead);
	change_pstate(philo, shutdown);
	print_death(philo);
	sem_post(philo->s_death);
	destroy_sems(philo);
	kill(0, SIGINT);
}

void	*check_death(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	while (check_pstate(philo, running) && !check_state(philo, done_eating))
	{
		sem_wait(philo->s_death);
		if (get_time_diff(philo->last_eat) > (size_t)philo->data->time_to_die)
		{
			is_dead(philo);
			return (NULL);
		}
		sem_post(philo->s_death);
		usleep(100);
	}
	return (NULL);
}

pthread_t	create_death_thread(t_philo *philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, check_death, philo);
	return (tid);
}

int	check_eat_counter(t_philo *philo)
{
	if (philo->data->max_eat != -1)
	{
		if (philo->eat_counter >= philo->data->max_eat)
		{
			change_state(philo, done_eating);
			return (1);
		}
	}
	return (0);
}

void	child_execution(t_philo *philo)
{
	init_child_sems(philo);
	philo->last_eat = get_timestamp();
	philo->tid = create_death_thread(philo);
	while (check_pstate(philo, running) && !check_state(philo, dead))
	{
		if (philo->index % 2 == 0 || !check_state(philo, undef))
			if (eat(philo) != 0)
				break ;
		if (check_eat_counter(philo) != 0)
			break ;
		change_state(philo, sleeping);
		print_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		change_state(philo, thinking);
		print_status(philo, THINK);
	}
	pthread_join(philo->tid, NULL);
	destroy_sems(philo);
}
