/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:24:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/02 13:22:56 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"
#include <sys/time.h>

void	*even_think_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while(*sopher->semafor == 0)
		usleep(10);
	usleep(100);
	think(sopher, start);
	while(1)
	{
		even_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
	// */
	// return (NULL);
}

void	*even_eat_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;
	
	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while(*sopher->semafor == 0)
		usleep(10);
	while(1)
	{
		even_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
	return (NULL);
}



pthread_t	*even_start_threads_immortal(t_philo *sopher, t_start *start)
{
	int	i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 2);
	if (thread == NULL)
		return (0);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (puterror("malloc failed\n"), free(thread), NULL);
		if(i % 2 == 0)
			if (pthread_create(thread + i,NULL, even_eat_immortal, args) != 0)
				return(puterror("error thread canno't be created\n"), free(thread), NULL);
		if (i % 2 == 1)
			if (pthread_create(thread + i,NULL, even_think_immortal, args) != 0)
				return(puterror("error thread can not be created\n"), free(thread), NULL);
		i ++;
	}
	return (thread);
}

void	even_philosophers_immortal(t_philo *sopher, t_start *start);

void	even_immortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;
	int			i;

	thread = even_start_threads_immortal(sopher, start);
	if (thread == NULL)
		return (free(sopher->print), free(sopher));
	even_philosophers_immortal(sopher, start);
	i = 0;
	while (i < start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i ++;
	}
	free(thread);
	free(sopher->print);
	free(sopher);
	exit(0);
}


size_t	get_time_from_start(t_philo *sopher)
{
	struct timeval	t;
	size_t			i;

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

void	philo_died(t_philo *sopher, size_t time)
{
	print_died(sopher, time);
}

void	even_philosophers_immortal(t_philo *sopher, t_start *start)
{
	int		i;
	size_t	time;

	usleep(0);
	*sopher->start = get_time_in_size_t();
	// printf("sopher->start == in even_philosophers %lu\n", *sopher->start);
	*sopher->semafor = 1;
	while(*sopher->semafor == 1)
	{
		i = 0;
		// printf("in the loop\n");
		time = get_time_from_start(sopher);
		// printf("%lu == time\n", time);
		while(i < start->philosophers)
		{
			if (sopher->ate + start->die < time)
				philo_died(sopher + i, time);
			i++;
		}
	}
}

