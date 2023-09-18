/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:17 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/18 16:10:07 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	impar(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]) == 0)
	{
		printf("%s%ld %d has taken a fork\n%s", PURPLE, gettime(philo->Mesa),
			philo->id + 1, RESET);
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]);
		printf("%s%ld %d has taken a fork\n%s", PURPLE, gettime(philo->Mesa),
			philo->id + 1, RESET);
	}
	printf("imap12\n");
	printf("%s%ld %d is eating\n%s", BYELLOW, gettime(philo->Mesa), philo->id
		+ 1, RESET);
	usleep(philo->Mesa->tte * 1000);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
}

void	par(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_r]) == 0)
	{
		printf("%s%ld %d has taken a fork\n%s", PURPLE, gettime(philo->Mesa),
			philo->id + 1, RESET);
		pthread_mutex_lock(&philo->Mesa->mutex_fork[philo->fork_l]);
		printf("%s%ld %d has taken a fork\n%s", PURPLE, gettime(philo->Mesa),
			philo->id + 1, RESET);
	}
	printf("imap1\n");
	printf("%s%ld %d is eating\n%s", BYELLOW, gettime(philo->Mesa), philo->id
		+ 1, RESET);
	usleep(philo->Mesa->tte * 1000);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
	//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
		par(philo);
	else if (philo->id % 2 != 0)
		impar(philo);
	pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
	pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
	philo->last_eaten = gettime(philo->Mesa);
	pthread_mutex_lock(&philo->Mesa->check);
	if (philo->Mesa->notepme > 0)
		philo->times_eaten++;
	if (philo->times_eaten == philo->Mesa->notepme)
		philo->Mesa->all_full++;
	pthread_mutex_unlock(&philo->Mesa->check);
}

void	my_sleep(t_philo *philo)
{
	printf("%s%ld %d is sleeping\n%s", BCYAN, gettime(philo->Mesa), philo->id
		+ 1, RESET);
	usleep(philo->Mesa->tts * 1000);
}

int	check_dead(t_philo *philo) {
	pthread_mutex_lock(&philo->Mesa->somebody_died);
	if (philo->Mesa->died)
	{
		printf("philo->died%d\n", philo->Mesa->died);
		pthread_mutex_unlock(&philo->Mesa->somebody_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->somebody_died);
	return (0);
}

int	check_notepme(t_philo *philo) {
	pthread_mutex_lock(&philo->Mesa->check);
	if (philo->Mesa->all_full == philo->Mesa->n_philo)
	{
		pthread_mutex_unlock(&philo->Mesa->check);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->check);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->fork_l = (philo->id + 1) % philo->Mesa->n_philo;
	philo->fork_r = philo->id;
	while (1)
	{
		/* if (philo->id + 1 % 2 == 0)
			usleep(100); */
		// comer dormir pensar
		eating(philo);
		printf("sleep");
		my_sleep(philo);
		printf("think");
		printf("%s%ld %d is thinking\n%s", BGREEN, gettime(philo->Mesa),
			philo->id + 1, RESET);
		//printf("%ld %d\n", (gettime(philo->Mesa->st)), philo->id);
		if (check_dead(philo))
			break ;
		if (check_notepme(philo))
			break ;
	}
	return (0);
}
