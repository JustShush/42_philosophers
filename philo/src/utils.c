/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:46:32 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/25 17:39:01 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error(int op, char *arg)
{
	if (op == 0)
		return (0);
	if (op == 1 && arg)
	{
		printf("%sERROR%s: %s", BRED, RESET, arg);
		return (0);
	}
	return (1);
}

time_t	baittime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

// get time in ms
time_t	gettime(t_philo *philo)
{
	return (baittime() - philo->Mesa->start_run);
}

void	vars_init(t_mesa *mesa)
{
	mesa->n_philo = 0;
	mesa->ttd = 0;
	mesa->tte = 0;
	mesa->tts = 0;
	mesa->notepme = 0;
	mesa->died = 0;
	mesa->all_full = 0;
}

void	free_thread(t_mesa *mesa)
{
	free(mesa->thread);
	free(mesa->philo);
	free(mesa->mutex_fork);
}

void	p_state(t_philo *philo, char *c, char *str)
{
	pthread_mutex_lock(&philo->Mesa->print);
	printf("%s%ld %d %s%s\n", c, gettime(philo), philo->id + 1, str, RESET);
	pthread_mutex_unlock(&philo->Mesa->print);
}
