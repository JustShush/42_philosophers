/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:48:10 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/13 11:13:23 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	baittime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

// get time in ms
time_t	gettime(t_philo *philo)
{
	return (baittime() - philo->_mesa->start_run);
}

void	my_sleep(t_philo *philo)
{
	p_state(philo, BCYAN, "is sleeping");
	usleep(philo->_mesa->tts * 1000);
	p_state(philo, BGREEN, "is thinking");
}
