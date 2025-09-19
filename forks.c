/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:43:36 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 13:44:37 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

static void	last_fork(t_philo *sopher, pthread_mutex_t *mut, int i)
{
	if (i % 2 == 1)
	{
		sopher[i].fork1 = mut + i + 1;
		sopher[i].fork2 = mut + 1;
	}
	else
	{
		sopher[i].fork1 = mut + 1;
		sopher[i].fork2 = mut + i + 1;
	}
	sopher[i].print = mut;
}

void	fill_philosophers_with_mutexes(t_philo *sopher,
									t_start *start, pthread_mutex_t *mut)
{
	int	i;

	i = 0;
	while (i < start->philosophers - 1)
	{
		if (i % 2 == 1)
		{
			sopher[i].fork1 = mut + i + 1;
			sopher[i].fork2 = mut + i + 2;
		}
		else
		{
			sopher[i].fork1 = mut + i + 2;
			sopher[i].fork2 = mut + i + 1;
		}
		sopher[i].print = mut;
		i ++;
	}
	last_fork(sopher, mut, i);
}

int	initialize_mutexes(t_philo *sopher, t_start *start, pthread_mutex_t *mut)
{
	int		i;

	mut = ft_calloc(sizeof(pthread_mutex_t), start->philosophers + 1);
	if (mut == NULL)
		return (free(sopher), puterror("malloc failed\n"), 0);
	i = 0;
	while (i <= start->philosophers)
	{
		if (pthread_mutex_init(mut + i, NULL))
			return (free(sopher), free_mutex(mut, start),
				puterror("failed to create mutex\n"), 0);
		i ++;
	}
	fill_philosophers_with_mutexes(sopher, start, mut);
	return (1);
}
