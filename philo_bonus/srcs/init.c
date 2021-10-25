/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:35:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 21:38:44 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	init_data(int ac, char **av)
{
	t_data	data;

	data.nb_philo = ft_atol(av[1]);
	data.time_to_die = ft_atol(av[2]);
	data.time_to_eat = ft_atol(av[3]);
	data.time_to_sleep = ft_atol(av[4]);
	data.max_eat = -1;
	data.state = running;
	data.pid_arr = NULL;
	if (ac > 5)
		data.max_eat = ft_atol(av[5]);
	check_value_errors(data);
	return (data);
}

t_philo	init_philo(t_data *data, t_sema *sem)
{
	t_philo	philo;

	philo.pid = -1;
	philo.data = data;
	philo.sem = sem;
	philo.eat_counter = 0;
	philo.last_eat = -1;
	philo.state = undef;
	return (philo);
}

t_sema	init_sem(int nb_philo)
{
	t_sema	sem;

	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("pstate");
	sem.s_forks = sem_open("forks", O_CREAT, 0666, nb_philo);
	sem.s_print = sem_open("print", O_CREAT, 0666, 1);
	sem.s_pstate = sem_open("pstate", O_CREAT, 0666, 1);
	return (sem);
}

void	init_child_sems(t_philo *philo)
{
	sem_unlink("death");
	sem_unlink("state");
	philo->s_death = sem_open("death", O_CREAT, 0666, 1);
	philo->s_state = sem_open("state", O_CREAT, 0666, 1);
}
