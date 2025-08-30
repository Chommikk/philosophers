/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:54:27 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/30 10:30:31 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"


void	*odd_think_immortal(void *args)
{
	return (NULL);
}

void	*odd_think_mortal(void *args)
{
	return (NULL);
}

void	*odd_eat_immortal(void *args)
{
	return (NULL);
}
void	*odd_eat_mortal(void *args)
{
	return (NULL);
}

int		odd_start_threads_mortal(t_philo *sopher, t_start *start)
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
			return (puterror("malloc failed\n"), 0);
		/*
		if(i % 2 == 0)
			if (pthread_create(thread + 1,NULL, odd_eat_mortal, args) != 0)
				return(free(args), puterror("error thread canno't be created\n"), 0);
		if (i % 2 == 1)
			if (pthread_create(thread + 1,NULL, odd_think_mortal, args) != 0)
				return(free(args), puterror("error thread can not be created\n"), 0);
		*/
		free(args);
		i ++;
	}
	free(thread);
	return (1);
}
int		odd_start_threads_immortal(t_philo *sopher, t_start *start)
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
			return (free(thread), puterror("malloc failed\n"), 0);
		/*
		if(i % 2 == 0)
			if (pthread_create(thread + 1,NULL, odd_eat_immortal, args) != 0)
				return(free(args), puterror("error thread canno't be created\n"), 0);
		if (i % 2 == 1)
			if (pthread_create(thread + 1,NULL, odd_think_immortal, args) != 0)
				return(free(args), puterror("error thread can not be created\n"), 0);
		*/
		free(args);
		i ++;
	}
	free(thread);
	return (1);
}

void	odd_immortal(t_philo *sopher, t_start *start)
{
	if (odd_start_threads_immortal(sopher, start) == 0)
		return (free(sopher->print), free(sopher));
	free(sopher->print);
	free(sopher);

}

void	odd_mortal(t_philo *sopher, t_start *start)
{
	if (odd_start_threads_mortal(sopher, start) == 0)
		return (free(sopher->print), free(sopher));
	free(sopher->print);
	free(sopher);

}

void	odd_philosophers(t_philo *sopher, t_start *start)
{
	if (sopher->lifetime == -1)
		odd_immortal(sopher, start);
	else
		odd_mortal(sopher, start);
	exit(0);
}
