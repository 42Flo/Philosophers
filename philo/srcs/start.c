/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:56:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 16:03:41 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_start_val(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_start);
	philo->started = true;
	pthread_mutex_unlock(&philo->m_start);
}

bool	check_start_val(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->m_start);
	if (philo->started)
		ret = true;
	pthread_mutex_unlock(&philo->m_start);
	return (ret);
}
