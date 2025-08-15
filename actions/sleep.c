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

void	eat(t_philo *philo, t_start *info, t_data *data)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	
	if (gettimeofday(&start, NULL) != 0)
		return ; //error handle
	print_eating(data, philo->name);
	if (info->die < ((start.tv_sec - philo->ate.tv_sec) * 1000UL + (start.tv_usec - philo->ate.tv_usec) / 1000))
		return ; //end thread philo died
	philo->ate = start;
	while (time > info->eat)
	{
		if (gettimeofday(&end, NULL) != 0)
			return ; //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	}
}
