/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:53:59 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/20 11:54:02 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_destroy(t_philo_data *data)
{
	size_t	k;

	if (data->forks != NULL)
	{
		k = 0;
		while (k < data->nb)
			pthread_mutex_destroy(&data->forks[k++]);
		free(data->forks);
	}
	if (data->philos != NULL)
	{
		k = 0;
		while (k < data->nb)
		{
			pthread_mutex_destroy(&data->philos[k].eating);
			pthread_mutex_destroy(&data->philos[k].eaten);
			++k;
		}
		free(data->philos);
	}
	pthread_mutex_destroy(&data->mis_running);
}
