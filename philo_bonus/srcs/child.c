/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 20:09:36 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/20 18:27:38 by csegal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	is_dead(t_philo *philo)
{
	sem_post(philo->death);
	sem_wait(philo->sem->print);
	philo->state = dead;
	philo->data->state = shutdown;
	sem_unlink("death");
	sem_close(philo->death);
	print_death(philo);
	kill(0, SIGINT);
}

void	*check_death(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	while (philo->data->state == running && philo->state != done_eating)
	{
		sem_wait(philo->death);
		if (get_time_diff(philo->last_eat) > (size_t)philo->data->time_to_die)
			is_dead(philo);
		sem_post(philo->death);
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
			philo->state = done_eating;
			return (1);
		}
	}
	return (0);
}

void	child_execution(t_philo *philo)
{
	pthread_t	tid;

	philo->death = init_death_sem();
	philo->last_eat = get_timestamp();
	tid = create_death_thread(philo);
	while (philo->data->state == running && philo->state != dead)
	{
		if (philo->index % 2 == 0 || philo->state != undef)
			if (eat(philo) != 0)
				exit(0);
		if (check_eat_counter(philo) != 0)
			exit(0);
		philo->state = sleeping;
		print_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking;
		print_status(philo, THINK);
	}
	pthread_detach(tid);
}
