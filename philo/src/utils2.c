/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:52:38 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/27 19:16:09 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_one(t_philo *philo)
{
	if (philo->_mesa->n_philo == 1)
	{
		pthread_mutex_lock(&philo->_mesa->mutex_fork[philo->id]);
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

void	philo_init(t_mesa *mesa, int i)
{
	mesa->philo[i].id = i;
	mesa->philo[i].last_eaten = 0;
	mesa->philo[i].times_eaten = 0;
}

int	valid_args(char *str)
{
	if (!ft_isdigit(str))
		return (1);
	if (ft_atoi(str) <= 0)
		return (1);
	if (ft_strlen(str) >= 5)
		return (1);
	return (0);
}
