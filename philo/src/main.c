/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:45:54 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/05 17:40:15 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parse_arg(int argc, char *argv[], t_mesa *mesa)
{
	if (argc < 5 || argc > 6)
	{
		printf("%sInvalid%s number of args!\n", BRED, RESET);
		return (1);
	}
	if (argv[1] && argv[2] && argv[3] && argv[4])
	{
		mesa->n_philo = ft_atoi(argv[1]);
		mesa->ttd = ft_atoi(argv[2]);
		mesa->tte = ft_atoi(argv[3]);
		mesa->tts = ft_atoi(argv[4]);
	}
	if (argv[5] && ft_atoi(argv[5]) > 0)
		mesa->notepme = ft_atoi(argv[5]); // e se agrv[5] for 0????
	else
		mesa->notepme = -1;
	return (0);
}

int	die(t_philo *philo)
{
	int i;

	i = 0;
	//printf("%p\n", &philo->Mesa->somebody_died);
	while (i < philo->Mesa->n_philo)
	{
		//printf("gettime:%ld | philo->last_eaten: %ld | philo->Mesa->ttd: %d\n", gettime(philo), philo->last_eaten, philo->Mesa->ttd + 1);
		pthread_mutex_lock(&philo->Mesa->getime);
		//printf("run:%ld\n", philo->Mesa->start_run);
		if (gettime(philo) > (philo->last_eaten + philo->Mesa->ttd + 1))
		{
			pthread_mutex_lock(&philo->Mesa->check);
			printf("%s%ld %d died\n%s", BIRED, gettime(philo), philo->id
				+ 1, RESET);
			philo->Mesa->died = 1;
			pthread_mutex_unlock(&philo->Mesa->check);
			pthread_mutex_unlock(&philo->Mesa->getime);
			return (1);
		}
		i++;
		//pthread_mutex_unlock(&philo->Mesa->somebody_died);
		pthread_mutex_unlock(&philo->Mesa->getime);
	}
	return (0);
}

t_philo	philo_mesa_init(t_mesa *mesa)
{
	t_philo	test;

	test.Mesa = mesa;
	return (test);
}

int	full(t_philo *philo)
{
	pthread_mutex_lock(&philo->Mesa->full_check);
	int notepme = philo->Mesa->notepme;
	if (philo->times_eaten == notepme) {
		pthread_mutex_unlock(&philo->Mesa->full_check);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->full_check);
	/* pthread_mutex_lock(&philo->Mesa->full_check);
	//printf("all-full:%d | n_philo:%d\n", philo->Mesa->all_full, philo->Mesa->n_philo);
	if (philo->Mesa->all_full == philo->Mesa->n_philo)
	{
		//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_r]);
		//pthread_mutex_unlock(&philo->Mesa->mutex_fork[philo->fork_l]);
		pthread_mutex_lock(&philo->Mesa->check);
		philo->Mesa->died = 1;
		pthread_mutex_unlock(&philo->Mesa->check);
		pthread_mutex_unlock(&philo->Mesa->full_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->Mesa->full_check); */
	return (0);
}

void	*check_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (full(philo))
			break ;
		if (die(philo))
		{
			break ;
			//return (0);
		}
	}
	return (0);
}

int	create_threads(t_mesa *mesa)
{
	int	i;

	i = 0;
	mesa->philo = (t_philo *)malloc(sizeof(t_philo) * mesa->n_philo);
	mesa->thread = malloc(sizeof(pthread_t) * mesa->n_philo);
	pthread_create(&mesa->check_thread, NULL, check_thread, mesa->philo);
	while (i < mesa->n_philo)
	{
		mesa->philo[i] = philo_mesa_init(mesa);
		mesa->philo[i].id = i;
		mesa->philo[i].last_eaten = 0;
		if (pthread_create(&mesa->thread[i], NULL, routine,
				&mesa->philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < mesa->n_philo)
	{
		if (pthread_join(mesa->thread[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_join(mesa->check_thread, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mesa	mesa;

	vars_init(&mesa);
	if (parse_arg(argc, argv, &mesa))
		return (error(0, NULL));
	mutex_init(&mesa);
	mesa.start_run = baittime();
	if (create_threads(&mesa))
		return (error(1, "creating mesa threads"));
	mutex_destroy(&mesa);
	free_thread(&mesa);
	return (0);
}
