/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:17 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/13 15:59:35 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	impar(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_l]) == 0)
	{
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_r]);
	}
}

void	par(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_r]) == 0)
	{
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_l]);
	}
}

void	eating(t_philo *philo)
{
	int	notepme;

	notepme = philo->_mesa->notepme;
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, PURPLE, "has taken a fork");
	p_state(philo, BYELLOW, "is eating");
	pthread_mutex_lock(&philo->_mesa->getime);
	philo->last_eaten = gettime(philo);
	pthread_mutex_unlock(&philo->_mesa->getime);
	usleep(philo->_mesa->tte * 1000);
	pthread_mutex_lock(&philo->_mesa->full);
	if (notepme > 0)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->_mesa->full);
	pthread_mutex_lock(&philo->_mesa->full_check);
	if (philo->times_eaten == notepme)
		philo->_mesa->all_full++;
	pthread_mutex_unlock(&philo->_mesa->full_check);
}

// separate the philos
void	par_impar(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_r]);
	else
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_l]);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_l]);
	else
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->fork_r]);
}

int	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->_mesa->full_check);
	if (philo->_mesa->all_full == philo->_mesa->n_philo)
	{
		unlock_forks(philo);
		pthread_mutex_unlock(&philo->_mesa->full_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->_mesa->full_check);
	return (0);
}
