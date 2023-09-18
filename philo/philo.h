/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:53:13 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/18 15:05:52 by dimarque         ###   ########.fr       */
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
	int	id;
	int	times_eaten;
	time_t	last_eaten;
	int	full;
	int	fork_r;
	int	fork_l;
	struct s_mesa *Mesa;
}		t_philo;

typedef struct s_mesa
{
	int	n_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	notepme;
	int	ms;
	int	all_full;
	time_t	start_run;
	t_philo *philo;
	pthread_t *thread;
	pthread_t check_thread;
	pthread_mutex_t *mutex_fork;
	pthread_mutex_t somebody_died;
	pthread_mutex_t check;
	int	died;
}		t_mesa;

// in mutex_utils.c

void	mutex_init(t_mesa *mesa);
void	mutex_destroy(t_mesa *mesa);
// ---------------

// in routine.c

void	*routine(void *arg);
// ---------------

// in static.c

t_mesa	*Mesa(void);
// ---------------

// in utils.c

int		error(int op, char *arg);
time_t	gettime(t_mesa *mesa);
time_t	baittime(void);
void	vars_init(t_mesa *mesa);
void	free_thread(t_mesa *mesa);
// ---------------

#endif