/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:17:56 by fregulie          #+#    #+#             */
/*   Updated: 2021/10/18 13:20:50 by fregulie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	int_min_max_error(char *err_target, long val)
{
	if (val > INT_MAX || val < INT_MIN)
		exit_error(err_target, "value must be integer");
}

char	**init_arg_errors_array(void)
{
	char	**args;

	args = malloc(sizeof(char *) * 5);
	args[0] = ft_strdup(ARG1);
	args[1] = ft_strdup(ARG2);
	args[2] = ft_strdup(ARG3);
	args[3] = ft_strdup(ARG4);
	args[4] = ft_strdup(ARG5);
	return (args);
}

void	check_arg_errors(int ac, char **av)
{
	int		i;
	int		j;
	char	**args;

	args = init_arg_errors_array();
	i = 1;
	if (ac < 5 || ac > 6)
		exit_error("philo", "invalid number of arguments");
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				exit_error(args[i - 1], "bad argument format");
			j++;
		}
		i++;
	}
	free_2d((void **)args, 5);
}

void	check_value_errors(t_data data)
{
	if (data.nb_philo < 2)
		exit_error("number_of_philosophers", "value must be >= 2");
	int_min_max_error(ARG1, data.nb_philo);
	int_min_max_error(ARG2, data.time_to_die);
	int_min_max_error(ARG3, data.time_to_eat);
	int_min_max_error(ARG4, data.time_to_sleep);
	int_min_max_error(ARG5, data.max_eat);
}

void	exit_error(char *err_target, char *err)
{
	printf("%sError%s:%s %s: %s\n", URED, RED, RESET, err_target, err);
	exit(1);
}
