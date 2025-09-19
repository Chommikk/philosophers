/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:15:01 by mchoma            #+#    #+#             */
/*   Updated: 2025/09/19 13:44:45 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft/libft.h"

void	fill_philosophers(
					t_philo *sopher,
					t_start *start,
					atomic_size_t *semafor,
					atomic_char *flag
					)
{
	int		i;

	i = 0;
	while (i < start->philosophers)
	{
		sopher[i].name = i + 1;
		sopher[i].que = i;
		sopher[i].lifetime = start->lifetime;
		sopher[i].semafor = semafor;
		sopher[i].start = semafor + 1;
		sopher[i].ate = 0;
		sopher[i].flag = flag + i;
		flag[i] = 1;
		i ++;
	}
}

t_philo	*initialize_philosophers(
								t_start *start,
								pthread_mutex_t *mut,
								atomic_size_t *semafor,
								atomic_char *flag
								)
{
	t_philo	*sopher;

	sopher = ft_calloc(sizeof(t_philo), start->philosophers + 3);
	if (sopher == NULL)
		return (puterror("malloc failed\n"), NULL);
	if (initialize_mutexes(sopher, start, mut) == 0)
		return (NULL);
	fill_philosophers(sopher, start, semafor, flag);
	return (sopher);
}

void	initialize_simulation(t_start *start)
{
	t_philo				*sopher;
	pthread_mutex_t		*mut;
	atomic_size_t		semafor[2];
	atomic_char			flag[1048];

	ft_memset(flag, 0, 1048);
	mut = NULL;
	semafor[0] = 0;
	sopher = initialize_philosophers(start, mut, semafor, flag);
	if (sopher == NULL)
		return ;
	if (start->philosophers % 2 == 0)
	{
		if (start->lifetime == -1)
			even_immortal(sopher, start);
		else
			even_mortal(sopher, start);
	}
	else
		odd_philosophers(sopher, start);
}

int	initialize(t_start *arg, int argc, char **argv)
{
	arg->philosophers = ft_atoi(argv[1]);
	if (arg->philosophers < 1 || arg->philosophers > 999)
		return (puterror("Invalid argument in philosophers\n"), 0);
	arg->die = ft_atoi(argv[2]);
	if (arg->die < 1)
		return (puterror("Invalid argument in die\n"), 0);
	arg->eat = ft_atoi(argv[3]);
	if (arg->eat < 1)
		return (puterror("Invalid argument in eat\n"), 0);
	arg->sleep = ft_atoi(argv[4]);
	if (arg->sleep < 1)
		return (puterror("Invalid argument in sleep\n"), 0);
	if (argc == 6)
	{
		arg->lifetime = ft_atoi(argv[5]);
		if (arg->lifetime < 1)
			return (puterror("Invalid argument in lifetime\n"), 0);
	}
	else
		arg->lifetime = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_start	arguments;

	if (argc != 5 && argc != 6)
		return (puterror("Incorect amount of arguments\n"), 1);
	if (initialize(&arguments, argc, argv) == 0)
		return (0);
	initialize_simulation(&arguments);
}
