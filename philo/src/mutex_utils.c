/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:27 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/18 12:59:12 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_init(t_mesa *mesa)
{
	int i;

	mesa->mutex_fork = malloc(sizeof(pthread_mutex_t) * mesa->n_philo);
	i = 0;
	while (i < mesa->n_philo)
	{
		pthread_mutex_init(&mesa->mutex_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&mesa->somebody_died, NULL);
	pthread_mutex_init(&mesa->check, NULL);
}

void	mutex_destroy(t_mesa *mesa)
{
	int i;

	i = 0;
	while (i < mesa->n_philo)
	{
		pthread_mutex_destroy(&mesa->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&mesa->somebody_died);
	pthread_mutex_destroy(&mesa->check);
}
