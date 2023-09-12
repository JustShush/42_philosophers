/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:45:34 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/12 14:49:12 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <pthread.h>
# include <sys/time.h>

# include "lib/lib.h"

# define RESET "\033[0m"
# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BPURPLE "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	int	id;
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
	time_t	start_run;
	t_philo *philo;
	pthread_t *thread;
	pthread_mutex_t mutex_id;
}		t_mesa;

// in mutex_utils.c

void	mutex_init(t_mesa *mesa);
void	mutex_destroy(t_mesa *mesa);
// ---------------

// in utils.c

int		error(int op, char *arg);
time_t	gettime(void);
void	vars_init(t_mesa *mesa);
void	free_thread(t_mesa *mesa);
// ---------------

#endif