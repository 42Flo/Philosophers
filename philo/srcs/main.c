/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/21 14:06:18 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_mutex	mutex;
	t_philo	*philo;

	check_arg_errors(ac, av);
	data = init_data(ac, av);
	mutex = init_mutex(data.nb_philo);
	philo = init_philo(&data, &mutex);
	start_threads(philo);
	check_end(philo);
	join_threads(philo);
	destroy_shared_mutexes(philo);
	free_philo(philo);
	return (0);
}
