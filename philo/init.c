/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:56:03 by jmilesi           #+#    #+#             */
/*   Updated: 2024/04/23 23:25:49 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_philo_init_philos(t_philo_data *data)
{
	size_t	k;

	k = 0;
	while (k < data->nb)
	{
		data->philos[k].r_fork = &data->forks[(k + 1) % data->nb];
		data->philos[k].l_fork = &data->forks[k];
		data->philos[k].id = k;
		data->philos[k].last_eat = 0;
		data->philos[k].nb_ate = 0;
		data->philos[k].data = data;
		data->philos[k].thread_id = 0;
		if (pthread_mutex_init(&data->philos[k].eating, NULL)
			|| pthread_mutex_init(&data->philos[k].eaten, NULL))
			print_error(data, "Mutex init error");
		data->philos[k++].dead = 0;
	}
}

static void	_philo_init_forks(t_philo_data *data)
{
	size_t	k;

	k = 0;
	while (k < data->nb)
		if (pthread_mutex_init(&data->forks[k++], NULL))
			break ;
	if (k != data->nb)
		while (k-- != 0)
			pthread_mutex_destroy(&data->forks[k]);
}

void	philo_init(t_philo_data *data)
{
	data->forks = malloc(sizeof(*data->forks) * data->nb);
	if (data->forks == NULL)
		print_error(data, "Bad alloc");
	_philo_init_forks(data);
	data->philos = malloc(sizeof(*data->philos) * data->nb);
	if (data->philos == NULL)
		print_error(data, "Bad alloc");
	_philo_init_philos(data);
}
