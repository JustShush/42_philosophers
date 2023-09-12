/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:27 by dimarque          #+#    #+#             */
/*   Updated: 2023/09/12 12:38:51 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	mutex_init(t_mesa *mesa)
{
	pthread_mutex_init(&mesa->mutex_id, NULL);
}

void	mutex_destroy(t_mesa *mesa)
{
	pthread_mutex_destroy(&mesa->mutex_id);
}
