/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:56:24 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/30 09:56:51 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

t_args	*fill(t_philo *sopher, t_start *start)
{
	t_args	*rt;

	rt = ft_calloc(sizeof(t_args), 1);
	if (rt == NULL)
		return (NULL);
	rt->sopher = sopher;
	rt->start = start;
	return (rt);
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

int	death_check(t_philo *sopher, t_start *start)
{
	if (sopher->ate + start->die < get_time_from_start(sopher))
		return (0);
	return (1);
}

//numbers are just for string optimatization it sais " is dead\n"
void	print_died(t_philo *data, size_t passed)
{
	size_t				len;
	size_t				offset;
	char				str[100];
	
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len = len + philo_itoa(str + offset + len + 1, data->name);
	*(unsigned long long*)(str + len + 2) = 0xa6465696420;
	pthread_mutex_lock(data->print);
	write(1, str + offset, len + 8);
	pthread_mutex_unlock(data->print);
	*data->semafor = 2;
}

//numbers are just for string optimatization it sais " is eating\n"
void	print_eating(t_philo *data, size_t passed)
{
	size_t				len;
	size_t				offset;
	char				str[100];
	
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len = len + philo_itoa(str + offset + len + 1, data->name);
	*(unsigned long long*)(str + offset + len + 2) = 0x6974616520736920;
	*(unsigned long long*)(str + offset + len + 10) = 0xa676e;
	pthread_mutex_lock(data->print);
	write(1, str + offset, len + 8);
	pthread_mutex_unlock(data->print);
}

//numbers are just for string optimatization it sais " is eating\n"
void	print_fork(t_philo *data, size_t passed)
{
	size_t				len;
	size_t				offset;
	char				str[100];
	
	len = llutoa(str, passed, &offset);
	str[offset + len] = ' ';
	len = len + philo_itoa(str + offset + len + 1, data->name);
	*(unsigned long long*)(str + offset + len + 2) = 0x6b61742073616820;
	*(unsigned long long*)(str + offset + len + 10) = 0x726f662061206e65;
	*(unsigned long long*)(str + offset + len + 18) = 0xa6b;
	pthread_mutex_lock(data->print);
	write(1, str + offset, len + 20);
	pthread_mutex_unlock(data->print);
}
