/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:42:23 by fregulie          #+#    #+#             */
/*   Updated: 2021/09/24 22:22:14 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_mutex	mutex;
	t_philo	*philo;

	data = init_data(ac, av);
	mutex = init_mutex(data.nb_philo);
	philo = init_philo(&data, &mutex);
	start_threads(philo); //TODO error : thread failed to create / join
	check_death(philo);
	join_threads(philo);
	return (0);
}
