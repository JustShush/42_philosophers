/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:49:57 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/25 13:00:40 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*check_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->_mesa->n_philo == 1)
			break ;
		if (full(philo))
			break ;
		if (die(philo))
			break ;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->fork_l = (philo->id + 1) % philo->_mesa->n_philo;
	philo->fork_r = philo->id;
	philo->times_eaten = 0;
	while (1)
	{
		if (check_one(philo))
			break ;
		par_impar(philo);
		if (check_died(philo) || check_full(philo) || full(philo))
			break ;
		eating(philo);
		if (check_died(philo) || check_full(philo))
			break ;
		unlock_forks(philo);
		my_sleep(philo);
		if (check_died(philo) || check_full(philo))
			break ;
		p_state(philo, BGREEN, "is thinking");
	}
	return (0);
}
