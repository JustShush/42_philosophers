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

void	impar(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]) == 0)
	{
		p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
		p_state(philo, PURPLE, "has taken a fork");
	}
	p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000);
}

void	par(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]) == 0)
	{
		p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
		p_state(philo, PURPLE, "has taken a fork");
	}
	p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
		par(philo);
	else if (philo->id % 2 != 0)
		impar(philo);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
	pthread_mutex_lock(&philo->Mesa->full);
	philo->last_eaten = gettime(philo);
	printf("last_eaten: %ld\n", philo->last_eaten);
	if (philo->Mesa->notepme > 0)
		philo->times_eaten++;
	if (philo->times_eaten == philo->Mesa->notepme)
		philo->Mesa->all_full++;
	//printf("all-full:%d | n_philo:%d\n", philo->Mesa->all_full, philo->Mesa->n_philo);
	pthread_mutex_unlock(&philo->Mesa->full);
}

void	my_sleep(t_philo *philo)
{
	/* printf("%s%ld %d is sleeping\n%s", BCYAN, gettime(philo->Mesa), philo->id
		+ 1, RESET); */
	p_state(philo, BCYAN, "is sleeping");
	usleep(philo->Mesa->tts * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->fork_l = (philo->id + 1) % philo->Mesa->n_philo;
	philo->fork_r = philo->id;
	philo->times_eaten = 0;
	while (1)
	{
		/* if (philo->id + 1 % 2 == 0)
			usleep(100); */
		// comer dormir pensar
		eating(philo);
		pthread_mutex_lock(&philo->Mesa->check);
		if (philo->Mesa->died) {
			pthread_mutex_unlock(&philo->Mesa->check);
			pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
			pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
			break ;
			//exit (0);
		}
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->Mesa->check);
		my_sleep(philo);
		p_state(philo, BGREEN, "is thinking");
	}
	return (0);
}