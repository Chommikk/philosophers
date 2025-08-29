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
#include <unistd.h>

static unsigned long long	time_passed(t_philo *data)
{
	struct timeval	end;
	
	if (gettimeofday(&end, NULL) != 0)
		return (1); //error handle
	return ((end.tv_sec - data->start.tv_sec) * 1000ULL
		+ (end.tv_usec - data->start.tv_usec) / 1000);
}

size_t	llutoa(char *str, unsigned long long number, size_t *start_of_string)
{
	int					counter;

	counter = 12;
	if (number == 0)
	{
		str[0] = '0';
		*start_of_string = 0;
		return (1);
	}
	while (number != 0)
	{
		str[--counter] = (number % 10) + '0';
		number = number / 10;
	}
	*start_of_string = counter;
	return (12 - counter);
}

size_t	philo_itoa(char *str, size_t num)
{
	int i;
	i = 0;

	if (num >= 1000)
	{
		str[3] = num % 10 + '0';
		num = num / 10;
		i ++;
	}
	if (num >= 100)
	{
		str[2] = num % 10 + '0';
		num = num / 10;
		i ++;
	}
	if (num >= 10)
	{
		str[1] = num % 10 + '0';
		num = num / 10;
		i ++;
	}
	str[0] = num % 10 + '0';
	return (i);
}

void	print_eating(t_philo *data)
{
	unsigned long long	passed;
	size_t				len;
	size_t				offset;
	char				str[100];
	
	passed = time_passed(data);
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len ++;
	len = len + philo_itoa(str + offset + len, data->name);
	str[len + offset + 1] = ' ';
	str[len + offset + 2] = 'i';
	str[len + offset + 3] = 's';
	str[len + offset + 4] = ' ';
	str[len + offset + 5] = 'e';
	str[len + offset + 6] = 'a';
	str[len + offset + 7] = 't';
	str[len + offset + 8] = 'i';
	str[len + offset + 9] = 'n';
	str[len + offset + 10] = 'g';
	str[len + offset + 11] = '\n';
	write(1, str + offset, len + 12);
}

void	print_fork(t_philo *data)
{
	unsigned long long	passed;
	size_t				len;
	size_t				offset;
	char				str[100];
	
	passed = time_passed(data);
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len ++;
	len = len + philo_itoa(str + offset + len, data->name);
	str[len + offset + 1] = ' ';
	str[len + offset + 2] = 'h';
	str[len + offset + 3] = 'a';
	str[len + offset + 4] = 's';
	str[len + offset + 5] = ' ';
	str[len + offset + 6] = 't';
	str[len + offset + 7] = 'a';
	str[len + offset + 8] = 'k';
	str[len + offset + 9] = 'e';
	str[len + offset + 10] = 'n';
	str[len + offset + 11] = ' ' ;
	str[len + offset + 12] = 'a';
	str[len + offset + 13] = ' ';
	str[len + offset + 14] = 'f';
	str[len + offset + 15] = 'o';
	str[len + offset + 16] = 'r';
	str[len + offset + 17] = 'k';
	str[len + offset + 18] = '\n';
	write(1, str + offset, len + 19);
}

void	print_sleeping(t_philo *data)
{
	unsigned long long	passed;
	size_t				len;
	size_t				offset;
	char				str[100];
	
	passed = time_passed(data);
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len ++;
	len = len + philo_itoa(str + offset + len, data->name);
	str[len + offset + 1] = ' ';
	str[len + offset + 2] = 'i';
	str[len + offset + 3] = 's';
	str[len + offset + 4] = ' ';
	str[len + offset + 5] = 's';
	str[len + offset + 6] = 'l';
	str[len + offset + 7] = 'e';
	str[len + offset + 8] = 'e';
	str[len + offset + 9] = 'p';
	str[len + offset + 10] = 'i';
	str[len + offset + 11] = 'n';
	str[len + offset + 12] = 'g';
	str[len + offset + 13] = '\n';
	write(1, str + offset, len + 14);
}



void	print_thinking(t_philo *data)
{
	unsigned long long	passed;
	size_t				len;
	size_t				offset;
	char				str[100];
	
	passed = time_passed(data);
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len ++;
	len = len + philo_itoa(str + offset + len, data->name);
	str[len + offset + 1] = ' ';
	str[len + offset + 2] = 'i';
	str[len + offset + 3] = 's';
	str[len + offset + 4] = ' ';
	str[len + offset + 5] = 't';
	str[len + offset + 6] = 'h';
	str[len + offset + 7] = 'i';
	str[len + offset + 8] = 'n';
	str[len + offset + 9] = 'k';
	str[len + offset + 10] = 'i';
	str[len + offset + 11] = 'n';
	str[len + offset + 12] = 'g';
	str[len + offset + 13] = '\n';
	write(1, str + offset, len + 14);
}


void	print_died(t_philo *data)
{
	unsigned long long	passed;
	size_t				len;
	size_t				offset;
	char				str[100];
	
	passed = time_passed(data);
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len ++;
	len = len + philo_itoa(str + offset + len, data->name);
	str[len + offset + 1] = ' ';
	str[len + offset + 2] = 'd';
	str[len + offset + 3] = 'i';
	str[len + offset + 4] = 'e';
	str[len + offset + 5] = 'd';
	str[len + offset + 6] = '\n';
	write(1, str + offset, len + 7);
	*data->semafor = 2;
}
