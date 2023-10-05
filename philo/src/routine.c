/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:17 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/05 17:48:08 by dimarque         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->Mesa->full_check);
	int notepme = philo->Mesa->notepme;
	/* if (philo->times_eaten == notepme)
	{
		pthread_mutex_unlock(&philo->Mesa->full_check);
		return ;
	} */
	pthread_mutex_unlock(&philo->Mesa->full_check);
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, BYELLOW, "is eating");
	usleep(philo->Mesa->tte * 1000);
	pthread_mutex_lock(&philo->Mesa->full);
	if (notepme > 0)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->Mesa->full);
	pthread_mutex_lock(&philo->Mesa->getime);
	philo->last_eaten = gettime(philo);
	pthread_mutex_unlock(&philo->Mesa->getime);
	/* pthread_mutex_lock(&philo->Mesa->full_check);
	if (philo->times_eaten == notepme)
		philo->Mesa->all_full++;
	pthread_mutex_unlock(&philo->Mesa->full_check); */
}

void my_sleep(t_philo *philo)
{
	/* printf("%s%ld %d is sleeping\n%s", BCYAN, gettime(philo->Mesa), philo->id
		+ 1, RESET); */
	p_state(philo, BCYAN, "is sleeping");
	usleep(philo->Mesa->tts * 1000);
	p_state(philo, BGREEN, "is thinking");
}

int check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->Mesa->check);
	if (philo->Mesa->died)
	{
		// printf("someonde ided: %d\n", philo->Mesa->died);
		pthread_mutex_unlock(&philo->Mesa->check);
		unlock_forks(philo);
		// mutex_destroy(philo->Mesa);
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


void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->fork_l = (philo->id + 1) % philo->Mesa->n_philo;
	philo->fork_r = philo->id;
	philo->times_eaten = 0;
	while (1)
	{
		par_impar(philo);
		if (check_died(philo) || full(philo))
			break;
		eating(philo);
		if (check_died(philo) || full(philo))
			break;
		unlock_forks(philo);
		my_sleep(philo);
	}
	return (0);
}
