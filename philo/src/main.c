/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:45:54 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/12 15:28:59 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	parse_arg(int argc, char *argv[], t_mesa *mesa)
{
	if (argc < 5 || argc > 6)
	{
		printf("\033[1;31mInvalid\033[0m number of args!\n");
		return (1);
	}
	if (argv[1] && argv[2] && argv[3] && argv[4])
	{
		mesa->n_philo = ft_atoi(argv[1]);
		mesa->ttd = ft_atoi(argv[2]);
		mesa->tte = ft_atoi(argv[3]);
		mesa->tts = ft_atoi(argv[4]);
	}
	if (argv[5])
		mesa->notepme = ft_atoi(argv[5]);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//pthread_mutex_lock(&philo->Mesa->mutex_id);
	
	printf("%ld id:%d\n", (gettime() - philo->Mesa->start_run), philo->id);
	//pthread_mutex_unlock(&philo->Mesa->mutex_id);
	return (0);
}

t_philo	philo_mesa_init(t_mesa *mesa)
{
	t_philo	test;

	test.Mesa = mesa;
	return (test);
}

int	create_threads(t_mesa *mesa)
{
	int	i;

	i = 0;
	mesa->philo = (t_philo *)malloc(sizeof(t_philo) * mesa->n_philo);
	mesa->thread = malloc(sizeof(pthread_t) * mesa->n_philo);
	while (i < mesa->n_philo)
	{
		mesa->philo[i] = philo_mesa_init(mesa);
		mesa->philo[i].id = i + 1;
		//printf("id:%d\n", mesa->philo[i].id);
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
		printf("control.\n");
	}
	free_thread(mesa);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mesa	mesa;

	vars_init(&mesa);
	if (parse_arg(argc, argv, &mesa))
		return (error(0, NULL));
	mutex_init(&mesa);
	mesa.start_run = gettime();
	if (create_threads(&mesa))
		return (error(1, "creating mesa threads"));
	mutex_destroy(&mesa);
	return (0);
}
