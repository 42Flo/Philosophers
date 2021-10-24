/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:02:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 17:23:03 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_index_color(t_philo *philo)
{
	if (philo->index % 2 != 0)
		printf("%s", HBLU);
	else
		printf("%s", HRED);
}

void	print_action_color(t_philo *philo, char *status)
{
	if (!ft_strcmp(status, FORK))
		printf("%s", YEL);
	else if (check_state(philo, eating))
		printf("%s", GRN);
	else if (check_state(philo, sleeping))
		printf("%s", MAG);
	else if (check_state(philo, thinking))
		printf("%s", CYN);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->m_print);
	printf("%s%zums%s\t\t", UWHT,
		get_timestamp() - philo->data->first_time, RESET);
	print_index_color(philo);
	printf("%d%s\t%s%s\n", philo->index + 1, BRED, DEATH, RESET);
	pthread_mutex_unlock(&philo->mutex->m_print);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->mutex->m_print);
	if (check_pstate(philo, running) || (check_state(philo, dead)
			&& !ft_strcmp(status, DEATH)))
	{
		printf("%s%zums%s\t\t", UWHT,
			get_timestamp() - philo->data->first_time, RESET);
		if (check_state(philo, dead))
			printf("%s", BRED);
		else
			print_index_color(philo);
		printf("%d%s\t", philo->index + 1, RESET);
		print_action_color(philo, status);
		printf("%s%s\n", status, RESET);
	}
	pthread_mutex_unlock(&philo->mutex->m_print);
}
