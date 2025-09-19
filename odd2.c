/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:39:40 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 14:40:03 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"

void	odd_immortal_eat(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;

	pthread_mutex_lock(sopher->fork1);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
		return (pthread_mutex_unlock(sopher->fork1), philo_died(sopher, i));
	print_fork(sopher, i);
	pthread_mutex_lock(sopher->fork2);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
		return (pthread_mutex_unlock(sopher->fork1),
			pthread_mutex_unlock(sopher->fork2), philo_died(sopher, i));
	print_fork(sopher, i);
	print_eat(sopher, i);
	sopher->ate = i;
	usleep(start->eat - (start->eat / 4));
	while ((size_t)start->eat > (get_time_from_start(sopher) - i))
		usleep(10);
	pthread_mutex_unlock(sopher->fork1);
	pthread_mutex_unlock(sopher->fork2);
}

void	*odd_eat_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	while (1)
	{
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		usleep((2000 * start->eat) - 1000 * start->sleep);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}
