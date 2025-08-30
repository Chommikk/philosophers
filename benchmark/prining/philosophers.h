/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:13:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/30 09:57:16 by mchoma           ###   ########.fr       */
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
	size_t			start;
	size_t			ate;
	size_t			last;
}	t_philo;

typedef struct	s_args
{
	t_philo	*sopher;
	t_start	*start;
}	t_args;

void	even_philosophers(t_philo *sopher, t_start *start);
void	print_died(t_philo *data, size_t passed);
void	odd_philosophers(t_philo *sopher, t_start *start);
t_args	*fill(t_philo *sopher, t_start *start);
#endif
