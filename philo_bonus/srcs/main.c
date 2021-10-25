/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/24 21:40:24 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_sema	sem;
	t_philo	philo;

	check_arg_errors(ac, av);
	data = init_data(ac, av);
	sem = init_sem(data.nb_philo);
	philo = init_philo(&data, &sem);
	philo.data->first_time = get_timestamp();
	create_process(&philo);
	if (philo.pid == 0)
		child_execution(&philo);
	else
		parent_execution(&philo);
	return (0);
}

void	parent_execution(t_philo *philo)
{
	int	status;
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		waitpid(philo->data->pid_arr[i], &status, 0);
		i++;
	}
	free(philo->data->pid_arr);
	destroy_sems(philo);
}
