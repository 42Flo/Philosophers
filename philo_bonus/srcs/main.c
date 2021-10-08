/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/08 22:42:36 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;
	int		status;

	//TODO death checker in parent proc with kill command? philo array like in mutex version?
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
		sem_unlink("forks");
		sem_close(philo.sem);
	}
	return (0);
}
