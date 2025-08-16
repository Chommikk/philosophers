/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:00:21 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/15 20:22:55 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"
#include "../utils/message.h"
#include <sys/time.h>
#include <stdio.h>

void	sleep(t_philo *philo, t_start *info, t_data *data)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	
	if (gettimeofday(&start, NULL) != 0)
		return ; //error handle
	print_sleeping(data, philo->name);
	
	while (time > info->sleep)
	{
		if (gettimeofday(&end, NULL) != 0)
			return ; //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	}
}

void	eat_even(t_philo *philo, t_start *info, t_data *data)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);
	if (gettimeofday(&start, NULL) != 0)
		return ; //error handle
	if (info->die < ((start.tv_sec - philo->ate.tv_sec) * 1000UL + (start.tv_usec - philo->ate.tv_usec) / 1000))
	{
		print_died(data, philo->name);
		return ; //end thread philo died
	}
	print_eating(data, philo->name);
	philo->ate = start;
	while (time > info->eat)
	{
		if (gettimeofday(&end, NULL) != 0)
			return ; //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	}
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	think(t_philo *philo, t_start *info, t_data *data)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
		return ; //error handle
	if (info->die < ((start.tv_sec - philo->ate.tv_sec) * 1000UL + (start.tv_usec - philo->ate.tv_usec) / 1000))
	{
		print_died(data, philo->name);
		return ; //end thread philo died
	}
	print_thinking(data, philo->name);
	usleep(0);
}

