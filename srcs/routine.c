/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:21:25 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/28 15:52:44 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	philo->last_eat = get_timestamp();
	//if (philo->index % 2 != 0)
	//	usleep(philo->data->time_to_eat * 1000);
	while (philo->data->state == running && philo->state != dead)	
	//	(philo->data->max_eat == -1 || philo->eat_counter < philo->data->max_eat))
	{
		eat(philo);
		philo->state = sleeping; //
		print_status(philo, SLEEP);
		if (philo->data->state == shutdown || philo->state == dead)
			break ;
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = thinking; //
		print_status(philo, THINK);
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->mutex->print);
	if (philo->data->state == running || (philo->state == dead
				&& !ft_strcmp(status, DEATH)))
	{
		if (philo->state == dead)
			printf("%s", BRED);
		else if (philo->index % 2 != 0)
			printf("%s", BLU);
		else
			printf("%s", YEL);
		printf("%zu\t", get_timestamp() - philo->data->first_time);
		printf("%d\t%s\n", philo->index + 1, status);
		printf("%s", RESET);
	}
	pthread_mutex_unlock(&philo->mutex->print);
}

void	is_dead(t_philo *philo)
{
	philo->state = dead;
	philo->data->state = shutdown;
	print_status(philo, DEATH);
}

/*int		check_death(t_philo *philo)
{
	
}*/

void	check_death(t_philo *philo_t)
{
	int	i;
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (philo->data->state == running)
	{
		i = 0;
		while (philo[i].last_eat != -1 && philo->data->state == running && i < philo->data->nb_philo)
		{
			//pthread_mutex_lock(&philo->mutex->death);
			if (get_time_diff(philo[i].last_eat) > (size_t)philo->data->time_to_die)
			{
		//		printf("last eat - first time |%zu|, time diff |%zu|, time_to_die |%d|\n", philo[i].last_eat - philo->data->first_time, get_time_diff(philo[i].last_eat), philo->data->time_to_die);
				is_dead(&philo[i]);
			}
			//pthread_mutex_unlock(&philo->mutex->death);
			i++;
		}
	}
}
