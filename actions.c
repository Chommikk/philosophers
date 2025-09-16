/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:15:22 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/02 13:18:08 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

void	even_immortal_eat(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	pthread_mutex_lock(sopher->fork1);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	pthread_mutex_lock(sopher->fork2);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		pthread_mutex_unlock(sopher->fork2);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	print_eat(sopher, i);
	sopher->ate = i;
	usleep(start->eat - (start->eat / 4));
	while ((size_t)start->eat > (get_time_from_start(sopher) - i))
		usleep(10);
	pthread_mutex_unlock(sopher->fork1);
	pthread_mutex_unlock(sopher->fork2);
}

void	initialize_variables_in_thread(t_args *args, t_philo **sopher, t_start **start)
{
	*sopher = ((t_args *)args)->sopher;
	*start = ((t_args *)args)->start;
}

void	even_mortal_eat(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	pthread_mutex_lock(sopher->fork1);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	pthread_mutex_lock(sopher->fork2);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		pthread_mutex_unlock(sopher->fork2);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	print_eat(sopher, i);
	sopher->ate = i;
	sopher->lifetime --;
	if (sopher->lifetime == 0)
		*sopher->flag = 0;
	usleep(start->eat - (start->eat / 4));
	while ((size_t)start->eat > (get_time_from_start(sopher) - i))
		usleep(10);
	pthread_mutex_unlock(sopher->fork1);
	pthread_mutex_unlock(sopher->fork2);
}

void	philo_sleep(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
		philo_died(sopher, i);
	print_sleep(sopher, i);
	usleep(start->sleep - (start->sleep / 4));
	while ((size_t)start->sleep > (get_time_from_start(sopher) - i))
		usleep(10);
}

void	think(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
		philo_died(sopher, i);
	print_think(sopher, i);
}
