/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:54:35 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/20 11:54:36 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*_philo_state(t_state state)
{
	if (state == FORK_TAKEN)
		return ("has taken a fork");
	if (state == EATING)
		return ("is eating");
	if (state == SLEEPING)
		return ("is sleeping");
	if (state == THINKING)
		return ("is thinking");
	if (state == DIED)
		return ("died");
	return ("");
}

void	print_state(t_philo_data *data, int nb, t_state state)
{
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mut);
	if (philo_is_running(data) || state == DIED)
		printf("%-8ld%d %s\n", timestamp(), nb, _philo_state(state));
	pthread_mutex_unlock(&mut);
}

int	philo_is_running(t_philo_data *data)
{
	int	isrun;

	pthread_mutex_lock(&data->mis_running);
	isrun = data->is_running;
	pthread_mutex_unlock(&data->mis_running);
	return (isrun);
}

void	philo_set_running(t_philo_data *data, int run)
{
	pthread_mutex_lock(&data->mis_running);
	data->is_running = run;
	pthread_mutex_unlock(&data->mis_running);
}
