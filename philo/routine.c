/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:55:25 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/06 15:55:27 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo *const		philo = p;
	t_philo_data *const	data = philo->data;

	if (philo->id % 2)
		custom_sleep(philo, 4);
	while (philo_is_running(data))
	{
		philo_eat(philo);
		if (!philo_is_running(philo->data))
			break ;
		print_state(data, philo->id, SLEEPING);
		custom_sleep(philo, data->t_tosleep);
		print_state(data, philo->id, THINKING);
	}
	return (NULL);
}
