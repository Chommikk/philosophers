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

void	odd_immortal_eat(t_philo *sopher, t_start *start);
void	odd_immortal_eat(t_philo *sopher, t_start *start);

void	odd_immortal_eat(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;
	
	if (sopher-> que == 0)
	{
		// pthread_mutex_lock(sopher->print);
		// ft_putnbr_fd(sopher->name, 1);
		// ft_putstr_fd(" waiting\n", 1);
		// pthread_mutex_unlock(sopher->print);
		sopher->que = start->philosophers - 1;
		usleep(1000 * (start->eat));
	}
	else if (sopher-> que == 1 || sopher->que == (size_t)start->philosophers - 1)
	{
		usleep(500);
		sopher->que --;
	}
	else
		sopher->que --;
	pthread_mutex_lock(sopher->fork1);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	pthread_mutex_lock(sopher->fork2);
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		pthread_mutex_unlock(sopher->fork2);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	print_eat(sopher, i);
	sopher->ate = i;
	usleep(start->eat - (start->eat / 4));
	while ((size_t)start->eat > (get_time_from_start(sopher) - i))
		usleep(10);
	pthread_mutex_unlock(sopher->fork1);
	pthread_mutex_unlock(sopher->fork2);
}

void	odd_mortal_eat(t_philo *sopher, t_start *start)
{
	atomic_size_t	i;
	
	if (sopher-> que == 0)
	{
		// ft_putnbr_fd(sopher->name, 1);
		// ft_putstr_fd("waiting\n", 1);
		sopher->que = start->philosophers - 1;
		usleep(1000 * (start->eat));
	}
	else if (sopher-> que == 1 || sopher->que == (size_t)start->philosophers - 1)
	{
		usleep(500);
		sopher->que --;
	}
	else
		sopher->que --;
	pthread_mutex_lock(sopher->fork1);
	// printf("locked fork 1\n");
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		philo_died(sopher, i);
		return ;
	}
	print_fork(sopher, i);
	pthread_mutex_lock(sopher->fork2);
	// printf("locked fork 2\n");
	i = get_time_from_start(sopher);
	if (i > (start->die + sopher->ate))
	{
		pthread_mutex_unlock(sopher->fork1);
		pthread_mutex_unlock(sopher->fork2);
		philo_died(sopher, i);
		return ;
	}
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

void	*odd_eat_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while(*sopher->semafor == 0)
		usleep(10);
	while(1)
	{
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	*odd_eat_mortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while(*sopher->semafor == 0)
		usleep(10);
	while(1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
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
	while(*sopher->semafor == 0)
		usleep(10);
	usleep(100);
	think(sopher, start);
	while(1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	*odd_think_immortal(void *args)
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
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}

void	*odd_wait_immortal(void *args)
{
	t_philo	*sopher;
	t_start	*start;

	initialize_variables_in_thread(args, &sopher, &start);
	free(args);
	while(*sopher->semafor == 0)
		usleep(10);
	usleep(start->eat * 2000);
	think(sopher, start);
	while(1)
	{
		odd_immortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
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
	while(*sopher->semafor == 0)
		usleep(10);
	usleep(start->eat * 2000);
	think(sopher, start);
	while(1)
	{
		odd_mortal_eat(sopher, start);
		philo_sleep(sopher, start);
		think(sopher,start);
		if (*sopher->semafor == 2)
			return (NULL);
	}
}


pthread_t	*odd_start_threads_mortal(t_philo *sopher, t_start *start)
{
	int			i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers + 1);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (free(thread), puterror("malloc failed\n"), NULL);
		/*
		if (i == 0)
		{
			if (pthread_create(thread + i,NULL, odd_wait_mortal, args) != 0)
				return(puterror("error thread canno't be created\n"), NULL);
		}
		*/
		if(i % 2 == 0)
		{
			if (pthread_create(thread + i,NULL, odd_think_mortal, args) != 0)
				return(puterror("error thread canno't be created\n"), NULL);
		}
		if (i % 2 == 1)
			if (pthread_create(thread + i,NULL, odd_eat_mortal, args) != 0)
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

pthread_t	*odd_start_threads_immortal(t_philo *sopher, t_start *start)
{
	int	i;
	pthread_t	*thread;
	t_args		*args;

	thread = ft_calloc(sizeof(pthread_t), start->philosophers);
	if (thread == NULL)
		return (NULL);
	i = 0;
	while(i  < start->philosophers)
	{
		args = fill(sopher + i, start);
		if (args == NULL)
			return (free(thread), puterror("malloc failed\n"), NULL);
		if(i % 2 == 0)
			if (pthread_create(thread + i,NULL, odd_think_immortal, args) != 0)
				return(free(args), puterror("error thread canno't be created\n"), NULL);
		if (i % 2 == 1)
			if (pthread_create(thread + i,NULL, odd_eat_immortal, args) != 0)
				return(free(args), puterror("error thread can not be created\n"), NULL);
		i ++;
	}
	return (thread);
}

void	odd_immortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;
	int			i;

	thread = odd_start_threads_immortal(sopher, start);
	if (thread == NULL)
		return (free(sopher->print), free(sopher));
	philosophers_immortal(sopher, start);
	i = 0;
	while (i < start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i ++;
	}
	i = 0;
	while (i < start->philosophers)
	{
		pthread_mutex_destroy(sopher->print + i);
		i ++;
	}
	free(thread);
	free(sopher->print);
	free(sopher);
	exit(0);
}

void	odd_mortal(t_philo *sopher, t_start *start)
{
	pthread_t	*thread;
	int			i;

	thread = odd_start_threads_mortal(sopher, start);
	if (thread == NULL)
		return (free(sopher->print), free(sopher));
	philosophers_immortal(sopher, start);
	i = 0;
	while (i <= start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i ++;
	}
	i = 0;
	while (i < start->philosophers)
	{
		pthread_mutex_destroy(sopher->print + i);
		i ++;
	}
	free(thread);
	free(sopher->print);
	free(sopher);
	exit(0);
}
/*
void *one(void *args)
{
	
}

void	one_philosopher(t_philo *sopher, t_start *start)
{
	pthread_t	thread[1];
	int			i;

	
	i = 0;
	while (i <= start->philosophers)
	{
		pthread_join(thread[i], NULL);
		i ++;
	}
	free(sopher->print);
	free(sopher);
	exit(0);
}
*/
void	odd_philosophers(t_philo *sopher, t_start *start)
{
	// if (start->philosophers == 1)
		// one_philosopher(sopher, start);
	if (sopher->lifetime == -1)
		odd_immortal(sopher, start);
	else
		odd_mortal(sopher, start);
	exit(0);
}
