/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:35:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 15:58:43 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int ac, char **av)
{
	t_data	data;

	data.nb_philo = ft_atol(av[1]);
	data.time_to_die = ft_atol(av[2]);
	data.time_to_eat = ft_atol(av[3]);
	data.time_to_sleep = ft_atol(av[4]);
	data.max_eat = -1;
	data.state = running;
	if (ac > 5)
		data.max_eat = ft_atol(av[5]);
	check_value_errors(data);
	return (data);
}

t_mutex	init_mutex(int nb_philo)
{
	t_mutex	mutex;
	int		i;

	i = 0;
	mutex.m_forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (mutex.m_forks)
	{
		while (i < nb_philo)
		{
			pthread_mutex_init(&mutex.m_forks[i], NULL);
			i++;
		}
	}
	pthread_mutex_init(&mutex.m_print, NULL);
	pthread_mutex_init(&mutex.m_pstate, NULL);
	return (mutex);
}

t_philo	*init_philo(t_data *data, t_mutex *mutex)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].index = i;
		philo[i].started = false;
		philo[i].data = data;
		philo[i].mutex = mutex;
		philo[i].eat_counter = 0;
		philo[i].last_eat = -1;
		philo[i].state = undef;
		pthread_mutex_init(&(philo[i].m_eat_count), NULL);
		pthread_mutex_init(&(philo[i].m_death), NULL);
		pthread_mutex_init(&(philo[i].m_state), NULL);
		pthread_mutex_init(&(philo[i].m_start), NULL);
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
