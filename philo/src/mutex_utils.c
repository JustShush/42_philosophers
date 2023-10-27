/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:27 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/27 18:30:48 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	more_mutex_init(t_mesa *mesa)
{
	pthread_mutex_init(&mesa->getime, NULL);
	pthread_mutex_init(&mesa->check, NULL);
	pthread_mutex_init(&mesa->check_fork, NULL);
	pthread_mutex_init(&mesa->full, NULL);
	pthread_mutex_init(&mesa->full_check, NULL);
	pthread_mutex_init(&mesa->can_eat, NULL);
}

void	mutex_init(t_mesa *mesa)
{
	int	i;

	mesa->mutex_fork = malloc(sizeof(pthread_mutex_t) * mesa->n_philo);
	if (!mesa->mutex_fork)
		return ;
	i = 0;
	while (i < mesa->n_philo)
	{
		pthread_mutex_init(&mesa->mutex_fork[i], NULL);
		i++;
	}
	more_mutex_init(mesa);
}

void	more_mutex_destroy(t_mesa *mesa)
{
	pthread_mutex_destroy(&mesa->getime);
	pthread_mutex_destroy(&mesa->check);
	pthread_mutex_destroy(&mesa->check_fork);
	pthread_mutex_destroy(&mesa->full);
	pthread_mutex_destroy(&mesa->full_check);
	pthread_mutex_destroy(&mesa->can_eat);
}

void	mutex_destroy(t_mesa *mesa)
{
	int	i;

	i = 0;
	while (i < mesa->n_philo)
	{
		pthread_mutex_destroy(&mesa->mutex_fork[i]);
		i++;
	}
	more_mutex_destroy(mesa);
}
