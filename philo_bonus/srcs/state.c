/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:36:16 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 15:40:58 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//TODO change mutex to semaphores
void	change_pstate(t_philo *philo, int pstate)
{
	sem_wait(philo->sem->s_pstate);
	philo->data->state = pstate;
	sem_post(philo->sem->s_pstate);
}

bool	check_pstate(t_philo *philo, enum e_program_state pstate)
{
	bool	ret;

	ret = false;
	sem_wait(philo->sem->s_pstate);
	if (philo->data->state == pstate)
		ret = true;
	sem_post(philo->sem->s_pstate);
	return (ret);
}

void	change_state(t_philo *philo, int state)
{
	sem_wait(philo->s_state);
	philo->state = state;
	sem_post(philo->s_state);
}

bool	check_state(t_philo *philo, enum e_philo_state state)
{
	bool	ret;

	ret = false;
	sem_wait(philo->s_state);
	if (philo->state == state)
		ret = true;
	sem_post(philo->s_state);
	return (ret);
}
