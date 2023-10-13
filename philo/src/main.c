/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:45:54 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/13 12:10:02 by dimarque         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < philo->_mesa->n_philo)
	{
		pthread_mutex_lock(&philo->_mesa->getime);
		if (gettime(philo) > (philo->last_eaten + philo->_mesa->ttd + 1))
		{
			pthread_mutex_lock(&philo->_mesa->check);
			printf("%s%ld %d died\n%s", BIRED, gettime(philo), philo->id
				+ 1, RESET);
			philo->_mesa->died = 1;
			pthread_mutex_unlock(&philo->_mesa->check);
			pthread_mutex_unlock(&philo->_mesa->getime);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&philo->_mesa->getime);
	}
	return (0);
}

int	full(t_philo *philo)
{
	int	notepme;

	notepme = philo->_mesa->notepme;
	pthread_mutex_lock(&philo->_mesa->full);
	if (philo->times_eaten == notepme)
	{
		unlock_forks(philo);
		pthread_mutex_unlock(&philo->_mesa->full);
		return (1);
	}
	pthread_mutex_unlock(&philo->_mesa->full);
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
