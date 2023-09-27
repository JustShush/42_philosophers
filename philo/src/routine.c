/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:17 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/25 17:38:20 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void impar(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]) == 0)
	{
		p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
		p_state(philo, PURPLE, "has taken a fork");
	}
	/* p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000); */
}

void par(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]) == 0)
	{
		p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
		p_state(philo, PURPLE, "has taken a fork");
	}
	/* p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000); */
}

void eating(t_philo *philo)
{
	p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000);
	pthread_mutex_lock(&philo->Mesa->getime);
	philo->last_eaten = gettime(philo);
	pthread_mutex_unlock(&philo->Mesa->getime);
	pthread_mutex_lock(&philo->Mesa->full);
	int notepme = philo->Mesa->notepme;
	if (notepme > 0)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->Mesa->full);
	pthread_mutex_lock(&philo->Mesa->full_check);
	if (philo->times_eaten == notepme)
		philo->Mesa->all_full++;
	pthread_mutex_unlock(&philo->Mesa->full_check);
}

void my_sleep(t_philo *philo)
{
	/* printf("%s%ld %d is sleeping\n%s", BCYAN, gettime(philo->Mesa), philo->id
		+ 1, RESET); */
	p_state(philo, BCYAN, "is sleeping");
	usleep(philo->Mesa->tts * 1000);
}

int check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->Mesa->check);
	if (philo->Mesa->died)
	{
		// printf("someonde ided: %d\n", philo->Mesa->died);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->Mesa->check);
		// mutex_destroy(philo->Mesa);
		return (1);
		// exit (0);
	}
	pthread_mutex_unlock(&philo->Mesa->check);
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->fork_l = (philo->id + 1) % philo->Mesa->n_philo;
	philo->fork_r = philo->id;
	philo->times_eaten = 0;
	while (1)
	{
		if (philo->id % 2 == 0)
			par(philo);
		else if (philo->id % 2 != 0)
			impar(philo);
		/* if (philo->id + 1 % 2 == 0)
			usleep(100); */
		// comer dormir pensar
		if (check_died(philo))
			break ;
		eating(philo);
		if (check_died(philo))
			break ;
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]); //! <---- FIX THIS UNLOCKS
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]); //! <---- FIX THIS UNLOCKS
		my_sleep(philo);
		p_state(philo, BGREEN, "is thinking");
	}
	return (0);
}
