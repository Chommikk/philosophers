/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:56:24 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 15:09:05 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

void	free_mutex(pthread_mutex_t *mut, t_start *start)
{
	int		i;

	if (mut == NULL)
		return ;
	i = 0;
	while (i <= start->philosophers)
	{
		pthread_mutex_destroy(mut + i);
		i ++;
	}
	free(mut);
}

void	thread_free(pthread_t *threads, t_philo *sopher)
{
	size_t	i;

	*sopher->flag = 2;
	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i], NULL);
		i ++;
	}
	free(threads);
}

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
	int	i;

	i = 0;
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
