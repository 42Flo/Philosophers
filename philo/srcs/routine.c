/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:21:25 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/25 14:33:15 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	pthread_mutex_lock(&philo->m_death);
	philo->last_eat = get_timestamp();
	pthread_mutex_unlock(&philo->m_death);
	init_start_val(philo);
	while (check_pstate(philo, running) && !check_state(philo, dead))
	{
		if (philo->index % 2 == 0 || !check_state(philo, undef))
			if (eat(philo) != 0)
				return (NULL);
		if (check_eat_counter(philo))
			return (NULL);
		change_state(philo, sleeping);
		print_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		if (check_pstate(philo, shutdown))
			return (NULL);
		change_state(philo, thinking);
		print_status(philo, THINK);
	}
	return (NULL);
}

void	is_dead(t_philo *philo)
{
	change_state(philo, dead);
	change_pstate(philo, shutdown);
	print_death(philo);
}

bool	check_eat_counter(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->m_eat_count);
	if (philo->data->max_eat != -1)
	{
		if (philo->eat_counter >= philo->data->max_eat)
		{
			change_state(philo, done_eating);
			ret = true;
		}
	}
	pthread_mutex_unlock(&philo->m_eat_count);
	return (ret);
}

void	check_end(t_philo *philo)
{
	int	i;
	int	all_done_eating;

	while (check_pstate(philo, running))
	{
		i = 0;
		all_done_eating = true;
		while (i < philo->data->nb_philo && philo->data->state == running)
		{
			if (!check_state(philo, done_eating))
				all_done_eating = false;
			pthread_mutex_lock(&philo[i].m_death);
			if (!check_state(philo, done_eating)
				&& check_start_val(philo)
				&& get_time_diff(philo[i].last_eat)
				> (size_t)philo->data->time_to_die)
				is_dead(&philo[i]);
			pthread_mutex_unlock(&philo[i].m_death);
			usleep(10);
			i++;
		}
		if (all_done_eating && !check_state(philo, undef))
			change_pstate(philo, shutdown);
	}
}
