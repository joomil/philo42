/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 23:13:19 by jmilesi           #+#    #+#             */
/*   Updated: 2023/12/08 23:15:57 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define ERR_BAD_ALLOC 1

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				dead;
	unsigned int	nb_ate;
	void			*data;
	time_t			last_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

typedef struct s_philo_data
{
	char			*pn;
	unsigned int	nb;
	int				is_running;
	pthread_mutex_t	mis_running;
	time_t			t_todie;
	time_t			t_toeat;
	time_t			t_tosleep;
	unsigned int	t_toeach;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_philo_data;

/* PARSE */

void			parse_args(t_philo_data *data, int argc, char **argv);

/* PHILO */

void			philo_init(t_philo_data *data);
void			philo_start(t_philo_data *data);
void			philo_destroy(t_philo_data *data);

void			*philo_routine(void *p);
void			philo_eat(t_philo *philo);
int				philo_is_running(t_philo_data *data);
void			philo_set_running(t_philo_data *data, int run);

void			print_error(t_philo_data *data, const char *s);
void			print_help(void);

time_t			timestamp(void);
void			custom_sleep(t_philo *philo, time_t duration);

/* LOG */

typedef enum e_state
{
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}				t_state;

void			print_state(t_philo_data *data, int nb, t_state type);

#endif