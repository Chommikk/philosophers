/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:54:27 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 15:08:37 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

void	*odd_think_immortal(void *args)
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
		if (*sopher->semafor == 2)
			return (NULL);
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		usleep((2000 * start->eat) - 1000 * start->sleep);
	}
}

void	*odd_wait_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while (*sopher->semafor == 0)
		usleep(10);
	think(sopher, start);
	usleep(start->eat * 2000);
	think(sopher, start);
	while (1)
	{
		if (*sopher->semafor == 2)
			return (NULL);
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
	}
}

static int	decider(void *args, pthread_t *thread, int i)
{
	t_philo	*sopher;
	t_start	*start;

	sopher = ((t_args *)args)->sopher;
	start = ((t_args *)args)->start;
	if (i == start->philosophers - 1)
	{
		if (pthread_create(thread + i, NULL, odd_wait_immortal, args) != 0)
			return (puterror("error thread canno't be created\n"),
				thread_free(thread, sopher), -1);
	}
	else if (i % 2 == 0)
	{
		if (pthread_create(thread + i, NULL, odd_think_immortal, args) != 0)
			return (puterror("error thread canno't be created\n"),
				thread_free(thread, sopher), -1);
	}
	else if (i % 2 == 1)
		if (pthread_create(thread + i, NULL, odd_eat_immortal, args) != 0)
			return (puterror("error thread can not be created\n"),
				thread_free(thread, sopher), -1);
	return (1);
}

pthread_t	*odd_start_threads_immortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers);
	if (thread == NULL)
		return (NULL);
	i = 0;
	while (i < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (thread_free(thread, sopher),
				puterror("malloc failed\n"), NULL);
		if (decider(args, thread, i) == -1)
			return (NULL);
		i ++;
	}
	return (thread);
}

void	odd_immortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;

	thread = odd_start_threads_immortal(sopher, start);
	if (thread == NULL)
		return (free_mutex(sopher->print, start), free(sopher));
	philosophers_immortal(sopher, start);
	if (start->philosophers == 1)
	{
		pthread_mutex_unlock(sopher->fork1);
	}
	return (thread_free(thread, sopher),
		free_mutex(sopher->print, start), free(sopher), exit(0));
}
