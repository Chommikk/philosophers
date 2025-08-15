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

static unsigned long long	time_passed(t_data *data)
{
	struct timeval	end;
	
	if (gettimeofday(&end, NULL) != 0)
		return (1); //error handle
	return ((end.tv_sec - data->start.tv_sec) * 1000ULL
		+ (end.tv_usec - data->start.tv_usec) / 1000);
}


void	print_eating(t_data *data, size_t num)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is eating\n", passed, num);
}

void	print_fork(t_data *data, size_t num)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu has taken a fork\n", passed, num);
}

void	print_sleeping(t_data *data, size_t num)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is sleeping\n", passed, num);
}

void	print_thinking(t_data *data, size_t num)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu is thinking\n", passed, num);
}

void	print_died(t_data *data, size_t num)
{
	unsigned long long	passed;

	passed = time_passed(data);
	printf("%llu %lu died\n", passed, num);
}
