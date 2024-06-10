/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:54:29 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/20 13:32:03 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_philo_wait_thread(t_philo_data *data)
{
	size_t	k;

	k = 0;
	while (k < data->nb)
	{
		if (data->philos[k].thread_id != 0)
			pthread_join(data->philos[k].thread_id, NULL);
		++k;
	}
}

static void	_philo_check_each(t_philo_data *data)
{
	size_t			k;
	unsigned int	nb_ate;

	k = 0;
	while (k < data->nb && data->t_toeach != __INT_MAX__)
	{
		pthread_mutex_lock(&data->philos[k].eaten);
		nb_ate = data->philos[k].nb_ate;
		pthread_mutex_unlock(&data->philos[k].eaten);
		if (nb_ate < (unsigned int) data->t_toeach)
			break ;
		++k;
	}
	if (k == data->nb)
		philo_set_running(data, 0);
}

static void	_philo_died(t_philo_data *data)
{
	size_t	k;

	while (philo_is_running(data))
	{
		k = 0;
		while (k < data->nb)
		{
			pthread_mutex_lock(&data->philos[k].eating);
			if (timestamp() - data->philos[k].last_eat >= data->t_todie)
			{
				philo_set_running(data, 0);
				print_state(data, k, DIED);
				pthread_mutex_unlock(&data->philos[k].eating);
				break ;
			}
			pthread_mutex_unlock(&data->philos[k].eating);
			++k;
		}
		_philo_check_each(data);
	}
}

void	philo_start(t_philo_data *data)
{
	size_t	k;

	data->is_running = 1;
	k = 0;
	while (k < data->nb)
	{
		data->philos[k].last_eat = timestamp();
		if (pthread_create(&data->philos[k].thread_id, NULL,
				philo_routine, &data->philos[k]))
		{
			philo_set_running(data, 0);
			_philo_wait_thread(data);
			print_error(data, "Thread init error");
		}
		usleep(500);
		++k;
	}
	_philo_died(data);
	_philo_wait_thread(data);
}
