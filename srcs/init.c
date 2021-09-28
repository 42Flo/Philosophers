/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:35:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/27 19:30:46 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int ac, char **av)
{
	t_data	data;

	data.nb_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.max_eat = -1;
	if (ac > 5)
		data.max_eat = ft_atoi(av[5]);
	return (data);
}

t_mutex	init_mutex(int nb_philo)
{
	t_mutex	mutex;
	int		i;

	i = 0;
	mutex.forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (mutex.forks)
	{
		while (i < nb_philo)
		{
			pthread_mutex_init(&mutex.forks[i], NULL);
			i++;
		}
	}
	//TODO mutex for death??
	return (mutex);
}

t_philo	*init_philo(t_data data, t_mutex mutex)
{
	int	i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (!philo)
		return (NULL); //TODO clean error return
	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo[i].index = i;
		philo[i].data = &data;
		philo[i].mutex = &mutex;
		init_forks(philo, i);
		i++;
	}
	return (philo);
}

void	init_forks(t_philo *philo, int i)
{
	philo[i].fork[LEFT] = i;
	philo[i].fork[RIGHT] = i + 1;
	if (i == philo->data->nb_philo - 1)
		philo[i].fork[RIGHT] = 0;
}
