/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:43:17 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/15 20:17:32 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct	s_data
{
	pthread_mutex_t	*lock;
	int				counter;
	struct timeval	start;
}	t_data;

typedef	struct	s_philo
{
	pthread_mutex_t	*fork;
	size_t			name;
	struct timeval	ate;
}	t_philo;

typedef struct	s_start
{
	size_t	philosophers;
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	lifetime;
}	t_start;



#endif
