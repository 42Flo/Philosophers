/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:36:16 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 17:20:06 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//TODO change mutex to semaphores
void	change_pstate(t_philo *philo, int pstate)
{
	pthread_mutex_lock(&philo->mutex->m_pstate);
	philo->data->state = pstate;
	pthread_mutex_unlock(&philo->mutex->m_pstate);
}

bool	check_pstate(t_philo *philo, enum e_program_state pstate)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->mutex->m_pstate);
	if (philo->data->state == pstate)
		ret = true;
	pthread_mutex_unlock(&philo->mutex->m_pstate);
	return (ret);
}

void	change_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->m_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->m_state);
}

bool	check_state(t_philo *philo, enum e_philo_state state)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->m_state);
	if (philo->state == state)
		ret = true;
	pthread_mutex_unlock(&philo->m_state);
	return (ret);
}
