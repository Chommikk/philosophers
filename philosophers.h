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

// threads wait until semafor == 1;
typedef struct	s_data
{
	pthread_mutex_t	*lock;
	int				counter;
	struct timeval	start;
}	t_data;

//fork1 odd index
//fork 2 even index
typedef	struct	s_philo
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				*semafor;
	size_t			name;
	struct timeval	ate;
	struct timeval	start;
	ssize_t			dont_eat;
}	t_philo;

typedef struct	s_start
{
	size_t	philosophers;
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	lifetime;
}	t_start;

typedef struct	s_arg
{
	t_start	*start;
	t_philo	*philo;
	t_data	*data;
}	t_arg;

int	philo_sleep(t_philo *philo, t_start *info);
int	eat_even(t_philo *philo, t_start *info);
int	think(t_philo *philo, t_start *info);
void	even_philosophers(void *arg);

#endif
