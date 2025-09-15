/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:13:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/02 13:21:34 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>

typedef struct	s_start
{
	int	philosophers;
	int	die;
	int	eat;
	int	sleep;
	int	lifetime;
}	t_start;

typedef struct	s_philo
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	*print;
	int				name;
	int				*semafor;
	int				lifetime;
	char			*flag;
	size_t			*start;
	size_t			ate;
	size_t			last;
	size_t			que;
}	t_philo;

typedef struct	s_args
{
	t_philo	*sopher;
	t_start	*start;
}	t_args;

void	philosophers_immortal(t_philo *sopher, t_start *start);
void	odd_philosophers(t_philo *sopher, t_start *start);
void	even_mortal(t_philo *sopher, t_start *start);
void	initialize_simulation(t_start *start);
void	even_mortal_eat(t_philo *sopher, t_start *start);
void	*even_eat_mortal(void *args);
void	*monitoring(void *args);
void	initialize_variables_in_thread(t_args *args, t_philo **sopher, t_start **start);
void	philo_died(t_philo *sopher, size_t time);
size_t	get_time_from_start(t_philo *sopher);
void	even_philosophers(t_philo *sopher, t_start *start);
void	print_died(t_philo *data, size_t passed);
void	print_think(t_philo *data, size_t passed);
void	print_eat(t_philo *data, size_t passed);
void	print_sleep(t_philo *data, size_t passed);
void	print_fork(t_philo *data, size_t passed);
void	odd_philosophers(t_philo *sopher, t_start *start);
t_args	*fill(t_philo *sopher, t_start *start);
size_t	get_time_in_size_t(void);
size_t	get_time_from_start(t_philo *sopher);
int		death_check(t_philo *sopher, t_start *start);
void	even_immortal_eat(t_philo *sopher, t_start *start);
void	philo_sleep(t_philo *sopher, t_start *start);
void	think(t_philo *sopher, t_start *start);

void	even_immortal(t_philo *sopher, t_start *start);
void	even_mortal(t_philo *sopher, t_start *start);
#endif
