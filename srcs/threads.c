/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:16:59 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/24 21:12:56 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, routine, &philo[i]) != 0)
		{
			printf("create failed\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int		join_threads(t_philo *philo)
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

int		start_threads(t_philo *philo)
{
	philo->data->first_time = get_timestamp();
	if (!create_threads(philo))
		return (-1);
	//if (!join_threads(philo))
	//	return (-1);
	return (0);
}
