/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:00:33 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 14:36:39 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"
#include <sys/time.h>

void	philo_died(t_philo *sopher, size_t time)
{
	print_died(sopher, time);
}

void	odd_philosophers(t_philo *sopher, t_start *start)
{
	if (sopher->lifetime == -1)
		odd_immortal(sopher, start);
	else
		odd_mortal(sopher, start);
	exit(0);
}

atomic_size_t	get_time_from_start(t_philo *sopher)
{
	struct timeval	t;
	atomic_size_t	i;

	gettimeofday(&t, NULL);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (i - (*sopher->start));
}

size_t	get_time_in_size_t(void)
{
	struct timeval	t;
	size_t			i;

	gettimeofday(&t, NULL);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (i);
}

void	*monitoring(void *args)
{
	atomic_char	*arr;
	t_philo		*sopher;
	t_start		*start;
	int			i;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	arr = sopher->flag;
	while (1)
	{
		i = 0;
		while (i < start->philosophers)
		{
			if (arr[i] != 0)
				break ;
			i++;
		}
		if (i == start->philosophers)
			return (atomic_store(sopher->semafor, 2), NULL);
		if (atomic_load(sopher->semafor) == 2)
			return (NULL);
	}
}
