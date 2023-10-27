/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:53:13 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/27 18:30:51 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "header.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <pthread.h>
# include <sys/time.h>

# include "lib/lib.h"

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	time_t			last_eaten;
	int				full;
	int				fork_r;
	int				fork_l;
	struct s_mesa	*_mesa;
}		t_philo;

typedef struct s_mesa
{
	int				n_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	int				all_full;
	time_t			start_run;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_t		check_thread;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	getime;
	pthread_mutex_t	check;
	pthread_mutex_t	check_fork;
	pthread_mutex_t	full;
	pthread_mutex_t	full_check;
	pthread_mutex_t	can_eat;
	int				died;
}		t_mesa;

// in main.c

int		die(t_philo *philo);
int		full(t_philo *philo);
// ---------------

// in mutex_utils.c

void	mutex_init(t_mesa *mesa);
void	mutex_destroy(t_mesa *mesa);
// ---------------

// in routine.c

void	eating(t_philo *philo);
void	par_impar(t_philo *philo);
int		check_full(t_philo *philo);
// ---------------

// in threads.c

void	*check_thread(void *arg);
void	*routine(void *arg);
// ---------------

// in time.c

time_t	baittime(void);
time_t	gettime(t_philo *philo);
void	my_sleep(t_philo *philo);
// ---------------

// in utils.c

int		error(int op, char *arg);
t_philo	philo_mesa_init(t_mesa *mesa);
void	vars_init(t_mesa *mesa);
void	free_thread(t_mesa *mesa);
void	p_state(t_philo *philo, char *c, char *str);
// ---------------

// in utils2.c

int		check_one(t_philo *philo);
int		check_died(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		valid_args(char *str);
// ---------------

#endif