/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:33:50 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 20:41:24 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_process(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->pid_arr = malloc(sizeof(pid_t) * philo->data->nb_philo);
	while (i < philo->data->nb_philo)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			philo->index = i;
			return ;
		}
		philo->data->pid_arr[i] = philo->pid;
		i++;
	}
}
