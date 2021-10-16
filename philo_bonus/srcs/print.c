/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:02:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/15 17:10:55 by fregulie         ###   ########.fr       */
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
	else if (philo->state == eating)
		printf("%s", GRN);
	else if (philo->state == sleeping)
		printf("%s", MAG);
	else if (philo->state == thinking)
		printf("%s", CYN);
	else if (philo->state == dead)
		printf("%s", RED);
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->print);
	printf("%s%zums%s\t\t", UWHT,
			get_timestamp() - philo->data->first_time, RESET);
	if (philo->state == dead)
		printf("%s", BRED);
	else
		print_index_color(philo);
	printf("%d%s\t", philo->index + 1, RESET);
	print_action_color(philo, status);
	printf("%s%s\n", status, RESET);
	if (philo->state != dead)
		sem_post(philo->print);
}
