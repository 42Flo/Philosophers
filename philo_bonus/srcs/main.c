/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/20 14:01:15 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;
	int		status;

	check_arg_errors(ac, av);
	data = init_data(ac, av);
	philo = init_philo(&data);
	philo.data->first_time = get_timestamp();
	create_process(&philo);
	if (philo.pid == 0)
		child_execution(&philo);
	else
	{
		waitpid(-1, &status, 0);
		destroy_sems(&philo);
	}
	return (0);
}*/

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
}
