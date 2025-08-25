/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:48:31 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/15 17:02:59 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

static unsigned long long	time_passed(t_philo *data)
{
	struct timeval	end;
	
	if (gettimeofday(&end, NULL) != 0)
		return (1); //error handle
	return ((end.tv_sec - data->start.tv_sec) * 1000ULL
		+ (end.tv_usec - data->start.tv_usec) / 1000);
}


void	print_eating(t_philo *data)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is eating\n", passed, data->name);
}

void	print_fork(t_philo *data)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu has taken a fork\n", passed, data->name);
}

void	print_sleeping(t_philo *data)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is sleeping\n", passed, data->name);
}

void	print_thinking(t_philo *data)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is thinking\n", passed, data->name);
}

void	print_died(t_philo *data)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu died\n", passed, data->name);
//	exit(1);
}
