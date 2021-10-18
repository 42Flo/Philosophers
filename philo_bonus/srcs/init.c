/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:35:33 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/18 16:02:34 by fregulie         ###   ########.fr       */
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
	if (ac > 5)
		data.max_eat = ft_atol(av[5]);
	check_value_errors(data);
	return (data);
}

/*t_philo	init_philo(t_data *data)
{
	t_philo	philo;

	philo.data = data;
	sem_unlink("forks");
	sem_unlink("print");
	philo.print = sem_open("print", O_CREAT, 0666, 1);
	philo.forks = sem_open("forks", O_CREAT, 0666, data->nb_philo);
	philo.eat_counter = 0;
	philo.last_eat = -1;
	philo.state = undef;
	return (philo);
}*/

t_sema	init_sem(int nb_philo)
{
	t_sema	sem;

	sem_unlink("forks");
	sem_unlink("print");
	sem.forks = sem_open("forks", O_CREAT, 0666, nb_philo);
	sem.print = sem_open("print", O_CREAT, 0666, 1);
	return (sem);
}

void	init_philo(t_data *data, t_sema *sem)
{
	int		i;

	g_philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!g_philo)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		g_philo[i].index = i;
		g_philo[i].data = data;
		g_philo[i].sem = sem;
		g_philo[i].eat_counter = 0;
		g_philo[i].last_eat = -1;
		g_philo[i].state = undef;
	}
}
