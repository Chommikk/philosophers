/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oddmortal2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:04:45 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 15:07:07 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"

static int	decider(void *args, pthread_t *thread, int i)
{
	t_philo	*sopher;
	t_start	*start;

	sopher = ((t_args *)args)->sopher;
	start = ((t_args *)args)->start;
	if (i == start->philosophers - 1)
	{
		if (pthread_create(thread + i, NULL, odd_wait_mortal, args) != 0)
			return (puterror("error thread canno't be created\n"),
				thread_free(thread, sopher), -1);
	}
	else if (i % 2 == 0)
	{
		if (pthread_create(thread + i, NULL, odd_think_mortal, args) != 0)
			return (puterror("error thread canno't be created\n"),
				thread_free(thread, sopher), -1);
	}
	else if (i % 2 == 1)
		if (pthread_create(thread + i, NULL, odd_eat_mortal, args) != 0)
			return (puterror("error thread can not be created\n"),
				thread_free(thread, sopher), -1);
	return (1);
}

pthread_t	*odd_start_threads_mortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 1);
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
	args = fill(sopher, start);
	if (args == NULL)
		return (thread_free(thread, sopher), puterror("malloc failed\n"), NULL);
	if (pthread_create(thread + start->philosophers,
			NULL, monitoring, args) != 0)
		return (puterror("error thread can not be created\n"),
			thread_free(thread, sopher), NULL);
	return (thread);
}
