/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:21:25 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/28 15:52:44 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;
	int	eat_count;

	philo = (t_philo *)philo_p;
	eat_count = 0;
	while (!is_dead(philo) &&
			(philo->data->max_eat == -1 || eat_count < philo->data->max_eat))
	{
		eat(philo);
		eat_count++;
		//TODO print_status sleep
		usleep(philo->data->time_to_sleep * 1000);
		//TODO print status think
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->mutex->print);
	//TODO get/print timestamp
	printf("%d %s\n", philo->index, status);
	pthread_mutex_unlock(&philo->mutex->print);
}

int	is_dead(t_philo *philo)
{

}
