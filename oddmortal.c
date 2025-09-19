/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oddmortal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:20:40 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 15:06:54 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

void	odd_mortal_eat(t_philo *sopher, t_start *start)
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
	sopher->ate = i;
	print_eat(sopher, i);
	sopher->lifetime --;
	if (sopher->lifetime == 0)
		*sopher->flag = 0;
	usleep(start->eat - (start->eat / 4));
	while ((size_t)start->eat > (get_time_from_start(sopher) - i))
		usleep(10);
	pthread_mutex_unlock(sopher->fork1);
	pthread_mutex_unlock(sopher->fork2);
}

void	*odd_eat_mortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	while (1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		usleep((2000 * start->eat) - 1000 * start->sleep);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	*odd_think_mortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	usleep(100);
	think(sopher, start);
	while (1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		usleep((2000 * start->eat) - 1000 * start->sleep);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	*odd_wait_mortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	think(sopher, start);
	usleep(start->eat * 2000);
	while (1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	odd_mortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;

	thread = odd_start_threads_mortal(sopher, start);
	if (thread == NULL)
		return (free_mutex(sopher->print, start), free(sopher));
	philosophers_immortal(sopher, start);
	return (thread_free(thread, sopher),
		free_mutex(sopher->print, start), free(sopher), exit(0));
}
