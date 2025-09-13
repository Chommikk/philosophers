/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evenmortal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:13:00 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/02 13:38:07 by mchoma           ###   ########.fr       */
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
	while(*sopher->semafor == 0)
		usleep(10);
	// printf("%p adress check think\n", sopher->start);
	// printf("%lu value check think\n", *sopher->start);
	usleep(100);
	think(sopher, start);
	while(1)
	{
		// printf("in loop think\n");
		even_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
		{
			return (NULL);
		}
	}
}

void	*even_eat_mortal(void *args)
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
		// printf("in loop think\n");
		even_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
		{
			return (NULL);
		}
	}
}

void	*monitoring(void *args)
{
	char	*arr;
	t_philo	*sopher;
	t_start	*start;
	int		i;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	// printf("%p adress flag\n", sopher->flag);
	arr = sopher->flag;
	// printf("%p adress arr\n", arr);
	while (1)
	{
		i = 0;
		while (i < start->philosophers)
		{
			//write(1,"hello",5);
			// printf("arr[%i] == %i\n", i, arr[i]);
			if (arr[i] !=0)
				break;
			i = i + 1;
		}
		if (i == start->philosophers)
		{
			*sopher->semafor = 2;
			return (NULL);
		}
		if (*sopher->semafor == 2)
			return (NULL);
		// usleep(100);
	}
}

pthread_t	*even_start_threads_mortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 2);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (free(thread), puterror("malloc failed\n"), NULL);
		if(i % 2 == 0)
			if (pthread_create(thread + i,NULL, even_eat_mortal, args) != 0)
				return(puterror("error thread canno't be created\n"), NULL);
		if (i % 2 == 1)
			if (pthread_create(thread + i,NULL, even_think_mortal, args) != 0)
				return(puterror("error thread can not be created\n"), NULL);
		i ++;
	}
	args = fill(sopher, start);
	if (args == NULL)
		return (free(thread), puterror("malloc failed\n"), NULL);
	if (pthread_create(thread + start->philosophers, NULL, monitoring, args) != 0)
		return(puterror("error thread can not be created\n"), NULL);
	return (thread);
}


void	even_mortal(t_philo *sopher, t_start *start)
{
	int		i;
	size_t	time;
	pthread_t	*thread;

	thread = even_start_threads_mortal(sopher, start);
	if (thread == NULL)
		return (free(sopher->print), free(sopher));
	usleep(0);
	*sopher->start = get_time_in_size_t();
	*sopher->semafor = 1;
	while (*sopher->semafor == 1)
	{
		i = 0;
		time = get_time_from_start(sopher);
		while(i < start->philosophers)
		{
			if(sopher->ate + start->die < time)
				philo_died(sopher + i, time);
			i ++;
		}
	}
	i = 0;
	while (i <= start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(thread);
	free(sopher->print);
	free(sopher);
	exit(0);
}

