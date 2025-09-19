/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:24:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 14:03:26 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"

void	*even_think_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	pthread_mutex_lock(sopher->print);
	printf("here think immortal\n");
	pthread_mutex_unlock(sopher->print);
	while (atomic_load(sopher->semafor) == 0)
		usleep(10);
	pthread_mutex_lock(sopher->print);
	printf("here think immortal2\n");
	pthread_mutex_unlock(sopher->print);
	usleep(100);
	think(sopher, start);
	while (1)
	{
		if (atomic_load(sopher->semafor) == 2)
			return (NULL);
		even_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
	}
}

void	*even_eat_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	pthread_mutex_lock(sopher->print);
	printf("here eat immortal\n");
	pthread_mutex_unlock(sopher->print);
	while (atomic_load(sopher->semafor) == 0)
		usleep(10);
	pthread_mutex_lock(sopher->print);
	printf("here eat immortal2\n");
	pthread_mutex_unlock(sopher->print);
	while (1)
	{
		even_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher, start);
		if (atomic_load(sopher->semafor) == 2)
			return (NULL);
	}
	return (NULL);
}

pthread_t	*even_start_threads_immortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 2);
	if (thread == NULL)
		return (0);
	i = -1;
	while (++ i < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (puterror("malloc failed\n"),
				thread_free(thread, sopher), NULL);
		if (i % 2 == 0)
			if (pthread_create(thread + i, NULL, even_eat_immortal, args) != 0)
				return (puterror("error thread canno't be created\n"),
					thread_free(thread, sopher), NULL);
		if (i % 2 == 1)
			if (pthread_create(thread + i, NULL,
					even_think_immortal, args) != 0)
				return (puterror("error thread can not be created\n"),
					thread_free(thread, sopher), NULL);
	}
	return (thread);
}

void	even_immortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;
	int			i;

	thread = even_start_threads_immortal(sopher, start);
	if (thread == NULL)
		return (free_mutex(sopher->print, start), free(sopher));
	philosophers_immortal(sopher, start);
	i = 0;
	while (i < start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i ++;
	}
	free(thread);
	free_mutex(sopher->print, start);
	free(sopher);
	exit(0);
}

void	philosophers_immortal(t_philo *sopher, t_start *start)
{
	int				i;
	atomic_size_t	time;

	usleep(0);
	atomic_store(sopher->start, get_time_in_size_t());
	atomic_store(sopher->semafor, 1);
	while (atomic_load(sopher->semafor) == 1)
	{
		i = 0;
		time = get_time_from_start(sopher);
		while (i < start->philosophers)
		{
			if (sopher[i].ate + start->die < time)
				return (philo_died(sopher + i, time));
			i++;
		}
		usleep(10);
	}
}
