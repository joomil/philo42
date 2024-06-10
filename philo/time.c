/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:46:12 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/14 08:46:23 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	timestamp(void)
{
	static time_t	initime = -1;
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (initime == -1)
		initime = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - initime);
}

void	custom_sleep(t_philo *philo, time_t duration)
{
	time_t	now;

	now = timestamp();
	while (now + duration > timestamp())
	{
		if (!philo_is_running(philo->data))
			break ;
		usleep(((t_philo_data *)philo->data)->nb * 2);
	}
}
