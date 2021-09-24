/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/16 05:05:42 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *philo, int i)
{
	philo[i].fork[LEFT] = i;
	philo[i].fork[RIGHT] = i + 1;
	if (i == philo->data->nb_philo - 1)
		philo[i].fork[RIGHT] = 0;
}

t_philo	*init_philo(t_data data)
{
	int	i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (!philo)
		return (NULL); //TODO clean error return
	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo[i].data = &data;
		init_forks(philo, i);
		i++;
	}
	return (philo);
}

t_data	init_data(char **av)
{
	t_data	data;

	data.nb_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	data = init_data(av);
	philo = init_philo(data);
	return (0);
}
