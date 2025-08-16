#include "philosophers.h"
#include "libft/libft.h"

void	initialize_philosophers_even(t_start *start, t_philo *sophers, pthread_mutex_t *mut);

//code a fucnion that will be multi threaded
/*
void	startup_simulation(t_philo *sophers, t_start *start)
{
	size_t	i;

	i = 0;
	while(i < start->philosophers)
	{

	}

}

*/

void	even_philosophers(void *arg)
{
	t_arg	*idk;
	pthread_mutex_t	*mut;
	t_philo			*sophers;
	size_t		i;
	
	i = 0;
	idk = (t_arg *)arg;
	mut = ft_calloc(sizeof(pthread_mutex_t), idk->start->philosophers + 1);
	if (mut == NULL)
		return ; //error handle
	sophers = ft_calloc(sizeof(t_philo), idk->start->philosophers + 1);
	if (sophers == NULL)
		return ; //error handle
	while (i < idk->start->philosophers)
	{
		if (pthread_mutex_init(mut + i,NULL) != 0)
			return ; //error handle
		i ++;
	}
	idk->data->lock = mut;
	initialize_philosophers_even(idk->start, sophers, mut);
	startup_simulation(sophers, idk->start);

}

void	initialize_philosophers_mutex(t_start *start, t_philo *sophers, pthread_mutex_t *mut)
{
	size_t	i;

	i = 0;
	while (i < start->philosophers)
	{
		sophers[i].dont_eat = -1;
		if (i % 2 == 1)
		{
			sophers[i].fork1 =  mut + i;
			if (i + 1 == start->philosophers)
				sophers[i].fork2 = mut;
			else 
				sophers[i].fork2 = mut + i + 1;
		}
		else 
		{
			sophers[i].fork2 =  mut + i;
			if (i + 1 == start->philosophers)
				sophers[i].fork1 = mut;
			else 
				sophers[i].fork1 = mut + i + 1;
		}
		i ++;
	}
}

void	initialize_philosophers_else(t_start *start, t_philo *sophers)
{
	size_t	i;

	i = 0;
	while (i < start->philosophers)
	{
		sophers[i].name = i + 1;
		sophers[i].dont_eat = -1;
		i ++;
	}
}

void	initialize_philosophers_even(t_start *start, t_philo *sophers, pthread_mutex_t *mut)
{
	initialize_philosophers_mutex(start, sophers, mut);
	initialize_philosophers_else(start, sophers);
}

























