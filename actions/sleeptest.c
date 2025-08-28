/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2025/08/15 20:22:55 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"
#include "../utils/message.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	death_check(t_philo *philo, t_start *info)
{
	struct timeval	curent;

	if (gettimeofday(&curent, NULL) != 0)
		return (0); //error handle
	// printf( "%lu == time passed, %zu time to die\n", ((curent.tv_sec - philo->ate.tv_sec) * 1000UL + (curent.tv_usec - philo->ate.tv_usec) / 1000), info->die) ;
	
	if (info->die < ((curent.tv_sec - philo->ate.tv_sec) * 1000UL + (curent.tv_usec - philo->ate.tv_usec) / 1000))
	{

		print_died(philo);
		return (1); //end thread philo died
	}
	return (0);
}

int	philo_sleep(t_philo *philo, t_start *info)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	
	usleep(1);
	if (death_check(philo, info) == 1)
		return (0);
	print_sleeping(philo);
	if (gettimeofday(&end, NULL) != 0)
		return (0); //error handle
	time = (end.tv_sec - philo->ate.tv_sec) * 1000UL + (end.tv_usec - philo->ate.tv_usec) / 1000;
	while (time < info->sleep - info->eat)
	{
		if (gettimeofday(&end, NULL) != 0)
			return (0); //error handle
		time = (end.tv_sec - philo->ate.tv_sec) * 1000UL + (end.tv_usec - philo->ate.tv_usec) / 1000;
		usleep(1);
	}
	return (1);
}

int	eat_even(t_philo *philo, t_start *info)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	
	if (death_check(philo, info) == 1)
		return (0);
	pthread_mutex_lock(philo->fork1);
	print_fork(philo);
	pthread_mutex_lock(philo->fork2);
	print_fork(philo);
	if (gettimeofday(&start, NULL) != 0)
		return (0); //error handle
	if (death_check(philo, info) == 1)
		return (0);
	print_eating(philo);
	philo->ate = start;
	if (gettimeofday(&end, NULL) != 0)
		return (0); //error handle
	time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	while (time < info->eat)
	{
		if (gettimeofday(&end, NULL) != 0)
			return (0); //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
		usleep(10);
	}
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (1);
}

int	think(t_philo *philo, t_start *info)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
		return (0); //error handle
	if (death_check(philo, info) == 1)
		return (0);
	print_thinking(philo);
	usleep(10);
	return (1);
}
