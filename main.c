/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/08/25 01:19:03 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	init_main(char **av)
{
	t_args	a;

	a.nb_philo = ft_atoi(av[1]);
	a.time_to_die = ft_atoi(av[2]);
	a.time_to_eat = ft_atoi(av[3]);
	a.time_to_sleep = ft_atoi(av[4]);
	//TODO optional arg eat counter
	return (a);
}

void	take_fork(t_philo *philo)
{
	
}

void	is_eating(t_philo *philo, int n, struct timeval last_eat)
{
	pthread_mutex_lock(&(philo->mutex[n - 1]));
	if (n == philo->a.nb_philo)
		pthread_mutex_lock(&(philo->mutex[0]));
	else
		pthread_mutex_lock(&(philo->mutex[n]));
	//eat here!
	
	pthread_mutex_unlock(&(philo->mutex[n - 1]));
	if (n == philo->a.nb_philo)
		pthread_mutex_unlock(&(philo->mutex[0]));
	else
		pthread_mutex_unlock(&(philo->mutex[n]));
}

void	is_sleeping(t_philo *philo)
{

}

void	is_thinking(t_philo *philo)
{

}

void	*routine(void *p) //EAT / SLEEP / THINK
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->isdead == 0)
	{
		
	}
}

void	check_arg_errors(int ac, char **av)
{

}

void	init_threads(t_philo *philo)
{
	pthread_t	thread[philo->a.nb_philo];

	philo->isdead = 0;
	philo->i = 0;
	while (philo->i < philo->a.nb_philo)
	{
		pthread_create(&thread[philo->i], NULL, routine, philo);
		philo->i++;
	}
	philo->i = 0;
	while (philo->i < philo->a.nb_philo)
	{
		pthread_join(thread[philo->i], NULL);
		philo->i++;
	}
}

void	init_mutexs(t_philo *philo)
{
	int	i;

	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->a.nb_philo);
	philo->forks = malloc(sizeof(int) * philo->a.nb_philo);
	if (!philo->mutex || !philo->forks)
		return ; //TODO clean exit
	i = 0;
	while (i < philo->a.nb_philo)
	{
		pthread_mutex_init(&philo->mutex[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;
	
	/* philo.a = init_main(av); */

	/* struct timeval	testime; */
	/* struct timeval	testime2; */
	/* gettimeofday(&testime, NULL); */
	/* usleep(1000); */
	/* gettimeofday(&testime2, NULL); */
	/* printf("time |%ld|\n", testime2.tv_usec - testime.tv_usec); */
}
