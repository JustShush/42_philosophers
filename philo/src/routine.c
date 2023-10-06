/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:17 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/06 16:21:37 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void impar(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]) == 0)
	{
		//p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
		//p_state(philo, PURPLE, "has taken a fork");
	}
	/* p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000); */
}

void par(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]) == 0)
	{
		//p_state(philo, PURPLE, "has taken a fork");
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
		//p_state(philo, PURPLE, "has taken a fork");
	}
	/* p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000); */
}
void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{	
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
	}
	else if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
	}
}

void eating(t_philo *philo)
{
	int notepme = philo->Mesa->notepme;
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000);
	pthread_mutex_lock(&philo->Mesa->full);
	if (notepme > 0)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->Mesa->full);
	pthread_mutex_lock(&philo->Mesa->full_check);
	if (philo->times_eaten == notepme)
		philo->Mesa->all_full++;
	pthread_mutex_unlock(&philo->Mesa->full_check);
	pthread_mutex_lock(&philo->Mesa->getime);
	philo->last_eaten = gettime(philo);
	pthread_mutex_unlock(&philo->Mesa->getime);
}

void my_sleep(t_philo *philo)
{
	p_state(philo, BCYAN, "is sleeping");
	usleep(philo->Mesa->tts * 1000);
	p_state(philo, BGREEN, "is thinking");
}

int check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->Mesa->check);
	if (philo->Mesa->died)
	{
		pthread_mutex_unlock(&philo->Mesa->check);
		unlock_forks(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->check);
	return (0);
}

// separate the ohilos
void par_impar(t_philo *philo)
{
	if (philo->id % 2 == 0)
		par(philo);
	else if (philo->id % 2 != 0)
		impar(philo);
	
	/* if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
	else
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
	p_state(philo, PURPLE, "has taken a fork");
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
	else
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
	p_state(philo, PURPLE, "has taken a fork"); */
}

int	check_one(t_philo *philo)
{
	if (philo->Mesa->n_philo == 1)
	{
		p_state(philo, PURPLE, "has taken a fork");
		usleep(philo->Mesa->ttd * 1000);
		p_state(philo, BIRED, "died");
		return (1);
	}
	return (0);
}

int	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->Mesa->full_check);
	if (philo->Mesa->all_full == philo->Mesa->n_philo)
	{
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->Mesa->full_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->full_check);
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
		if (check_one(philo))
			break ;
		par_impar(philo);
		if (check_died(philo) || full(philo))
			break ;
		eating(philo);
		if (check_died(philo))
			break ;
		unlock_forks(philo);
		my_sleep(philo);
	}
	return (0);
}
