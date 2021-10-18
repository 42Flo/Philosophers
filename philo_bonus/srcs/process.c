/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:33:50 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/18 16:19:40 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*void	create_process(t_philo *philo)
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
}*/

t_philo	*create_process(void)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < g_philo->data->nb_philo)
	{
		g_philo[i].pid = fork();
		philo = &g_philo[i];
		if (philo->pid == 0)
			return (philo);
		i++;
	}
	return (philo);
}
