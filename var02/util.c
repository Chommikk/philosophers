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

void	print_died(t_philo *data, size_t passed)
{
	size_t				len;
	size_t				offset;
	char				str[100];
	
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
