/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:46:32 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/12 14:49:33 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

// get time in ms
time_t	gettime(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	vars_init(t_mesa *mesa)
{
	mesa->n_philo = 0;
	mesa->ttd = 0;
	mesa->tte = 0;
	mesa->tts = 0;
	mesa->notepme = 0;
	mesa->ms = 0;
}

void	free_thread(t_mesa *mesa)
{
	free(mesa->thread);
	free(mesa->philo);
}
