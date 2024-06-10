/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:55:50 by jmilesi           #+#    #+#             */
/*   Updated: 2024/05/20 11:55:51 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_philo_eat_take_rfork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_state(philo->data, philo->id, FORK_TAKEN);
}

static void	_philo_eat_take_lfork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_state(philo->data, philo->id, FORK_TAKEN);
}

static void	_philo_eat_take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		_philo_eat_take_rfork(philo);
		_philo_eat_take_lfork(philo);
	}
	else
	{
		_philo_eat_take_lfork(philo);
		if (philo->l_fork != philo->r_fork)
			_philo_eat_take_rfork(philo);
	}
}

void	philo_eat(t_philo *philo)
{
	_philo_eat_take_fork(philo);
	if (philo->r_fork == philo->l_fork)
	{
		while (philo_is_running(philo->data))
			usleep(50);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->eating);
	print_state(philo->data, philo->id, EATING);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->eating);
	custom_sleep(philo, ((t_philo_data *)philo->data)->t_toeat);
	pthread_mutex_lock(&philo->eaten);
	++philo->nb_ate;
	pthread_mutex_unlock(&philo->eaten);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
