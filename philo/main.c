/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 23:10:12 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/24 07:22:23 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac < 5 || ac > 6)
		print_help();
	parse_args(&data, ac, av);
	philo_init(&data);
	timestamp();
	philo_start(&data);
	philo_destroy(&data);
	return (EXIT_SUCCESS);
}
