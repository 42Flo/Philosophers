/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 21:29:58 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 12:33:10 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_2d(void **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

void	destroy_sems(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
	sem_close(philo->sem->forks);
	sem_close(philo->sem->print);
	sem_close(philo->death);
}
