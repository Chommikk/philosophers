/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evenmortal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:14:32 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 14:16:18 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

void	*even_think_mortal(void *args)
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
		even_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
	}
}

void	*even_eat_mortal(void *args)
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
		even_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
	}
}

static int	last_thread(t_philo *sopher, t_start *start, pthread_t *thread)
{
	void	*args;

	args = fill(sopher, start);
	if (args == NULL)
		return (thread_free(thread, sopher), puterror("malloc failed\n"), -1);
	if (pthread_create(thread + start->philosophers, NULL,
			monitoring, args) != 0)
		return (puterror("error thread can not be created\n"), -1);
	return (1);
}

pthread_t	*even_start_threads_mortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 2);
	i = 0;
	while (i < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (thread_free(thread, sopher),
				puterror("malloc failed\n"), NULL);
		if (i % 2 == 0)
			if (pthread_create(thread + i, NULL, even_eat_mortal, args) != 0)
				return (puterror("error thread canno't be created\n"),
					thread_free(thread, sopher), NULL);
		if (i % 2 == 1)
			if (pthread_create(thread + i, NULL, even_think_mortal, args) != 0)
				return (puterror("error thread can not be created\n"),
					thread_free(thread, sopher), NULL);
		i ++;
	}
	if (last_thread(sopher, start, thread) == -1)
		return (NULL);
	return (thread);
}

void	even_mortal(t_philo *sopher, t_start *start)
{
	int				i;
	atomic_size_t	time;
	pthread_t		*thread;

	thread = even_start_threads_mortal(sopher, start);
	if (thread == NULL)
		return (free_mutex(sopher->print, start), free(sopher), exit(1));
	usleep(0);
	*sopher->start = get_time_in_size_t();
	*sopher->semafor = 1;
	while (*sopher->semafor == 1)
	{
		i = 0;
		time = get_time_from_start(sopher);
		while (i < start->philosophers)
		{
			if (sopher->ate + start->die < time)
				philo_died(sopher + i, time);
			i ++;
		}
	}
	return (thread_free(thread, sopher),
		free_mutex(sopher->print, start), free(sopher), exit(0));
}
