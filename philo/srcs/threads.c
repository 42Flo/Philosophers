/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:16:59 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 17:02:46 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_join(philo[i].tid, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	start_threads(t_philo *philo)
{
	philo->data->first_time = get_timestamp();
	if (!create_threads(philo))
		return (-1);
	return (0);
}
