/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:35:19 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 16:05:36 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_shared_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo->mutex->m_forks[i]);
		pthread_mutex_destroy(&philo[i].m_death);
		pthread_mutex_destroy(&philo[i].m_state);
		pthread_mutex_destroy(&philo[i].m_eat_count);
		pthread_mutex_destroy(&philo[i].m_start);
		i++;
	}
	pthread_mutex_destroy(&philo->mutex->m_print);
	return (0);
}

void	free_philo(t_philo *philo)
{
	free(philo->mutex->m_forks);
	free(philo);
}

void	free_2d(void **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}
