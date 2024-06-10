/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:34:06 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/24 07:41:42 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atot(const char *s, time_t *t)
{
	time_t	k;

	if (*s == '\0')
		return (0);
	k = 0;
	while (*s >= '0' && *s <= '9')
	{
		k *= 10;
		k += *s - '0';
		++s;
	}
	*t = k;
	return (*s == '\0');
}

int	ft_atoui(const char *s, unsigned int *n)
{
	unsigned int	k;

	if (*s == '\0')
		return (0);
	k = 0;
	while (*s >= '0' && *s <= '9')
	{
		k *= 10;
		k += *s - '0';
		++s;
	}
	*n = k;
	return (*s == '\0');
}

void	parse_args(t_philo_data *data, int ac, char **av)
{
	data->pn = av[0];
	data->philos = NULL;
	data->is_running = 0;
	data->forks = NULL;
	if (!ft_atoui(av[1], &data->nb))
		print_error(data, "number_of_philosophers must be an natural integer");
	if (!ft_atot(av[2], &data->t_todie))
		print_error(data, "time_to_die must be an natural integer");
	if (!ft_atot(av[3], &data->t_toeat))
		print_error(data, "time_to_eat must be an natural integer");
	if (!ft_atot(av[4], &data->t_tosleep))
		print_error(data, "time_to_sleep must be an natural integer");
	if (ac == 6 && !ft_atoui(av[5], &data->t_toeach))
		print_error(data, "number_of_times_each_philosopher_must_eat \
must be an natural integer");
	else if (ac != 6)
		data->t_toeach = __INT_MAX__;
	if (data->nb == 0)
		print_error(data, "number_of_philosophers can't be null");
	if (pthread_mutex_init(&data->mis_running, NULL))
		print_error(data, "Mutex init error");
}
