/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:52:38 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/25 15:45:19 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_one(t_philo *philo)
{
	if (philo->_mesa->n_philo == 1)
	{
		p_state(philo, PURPLE, "has taken a fork");
		usleep(philo->_mesa->ttd * 1000);
		p_state(philo, BIRED, "died");
		return (1);
	}
	return (0);
}

int	check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->_mesa->check);
	if (philo->_mesa->died)
	{
		pthread_mutex_unlock(&philo->_mesa->check);
		unlock_forks(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->_mesa->check);
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->_mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->_mesa->mutex_fork[philo->fork_r]);
	}
	else if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->_mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->_mesa->mutex_fork[philo->fork_l]);
	}
}

int	valid_args(char *str)
{
	if (!ft_isdigit(str))
		return (1);
	return (0);
}
