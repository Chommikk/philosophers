/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:24:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/30 10:32:22 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include "libft/libft.h"
#include <sys/time.h>

void	*even_think_immortal(void *args)
{
	return (NULL);
}

void	*even_think_mortal(void *args)
{
	return (NULL);
}

void	*even_eat_immortal(void *args)
{
	return (NULL);
}
void	*even_eat_mortal(void *args)
{
	return (NULL);
}

int		even_start_threads_mortal(t_philo *sopher, t_start *start)
{
	int	i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (free(thread), puterror("malloc failed\n"), 0);
		/*
		if(i % 2 == 0)
		
			if (pthread_create(thread + 1,NULL, even_eat_mortal, args) != 0)
				return(free(args), puterror("error thread canno't be created\n"), 0);
		if (i % 2 == 1)
			if (pthread_create(thread + 1,NULL, even_think_mortal, args) != 0)
				return(free(args), puterror("error thread can not be created\n"), 0);
		*/
		free(args);
		i ++;
	}
	return (1);
}
int		even_start_threads_immortal(t_philo *sopher, t_start *start)
{
	int	i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers);
	if (thread == NULL)
		return (0);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (puterror("malloc failed\n"), 0);
		/*
		if(i % 2 == 0)
			if (pthread_create(thread + 1,NULL, even_eat_immortal, args) != 0)
				return(free(args), puterror("error thread canno't be created\n"), 0);
		if (i % 2 == 1)
			if (pthread_create(thread + 1,NULL, even_think_immortal, args) != 0)
				return(free(args), puterror("error thread can not be created\n"), 0);
		*/
		free(args);
		i ++;
	}
	return (1);
}

void	even_immortal(t_philo *sopher, t_start *start)
{
	if (even_start_threads_immortal(sopher, start) == 0)
		return (free(sopher->print), free(sopher));
	return (free(sopher->print), free(sopher));
}

void	even_mortal(t_philo *sopher, t_start *start)
{
	if (even_start_threads_mortal(sopher, start) == 0)
		return (free(sopher->print), free(sopher));
	return (free(sopher->print), free(sopher));
}

size_t	get_time_from_start(t_philo *sopher)
{
	struct timeval	t;
	size_t			i;

	gettimeofday(&t, NULL);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (i);
}

void	philo_died(t_philo *sopher, size_t time)
{
	*sopher->semafor = 2;
	print_died(sopher, time);
}

void	even_philosophers(t_philo *sopher, t_start *start)
{
	int		i;
	size_t	time;

	if (sopher->lifetime == -1)
		even_immortal(sopher, start);
	else
		even_mortal(sopher, start);
	*sopher->semafor = 1;
	while(*sopher->semafor == 1)
	{
		i = 0;
		time = get_time_from_start(sopher);
		while(i < start->philosophers)
		{
			if (sopher[i].ate + start->eat < i)
				philo_died(sopher + i, time);

		}

	}
}
