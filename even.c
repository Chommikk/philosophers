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
	t_start	*idk;
	pthread_mutex_t	*mut;
	t_philo			*sophers;
	size_t		i;
	
	i = 0;
	idk = (t_start *)arg;
	mut = ft_calloc(sizeof(pthread_mutex_t), idk->philosophers + 1);
	if (mut == NULL)
		return ; //error handle
	sophers = ft_calloc(sizeof(t_philo), idk->philosophers + 1);
	if (sophers == NULL)
		return ; //error handle
	while (i < idk->philosophers)
	{
		if (pthread_mutex_init(mut + i,NULL) != 0)
			return ; //error handle
		i ++;
	}
	initialize_philosophers_even(idk, sophers, mut);
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

void	initialize_philosophers_else(t_start *start, t_philo *sophers, int *semafor)
{
	size_t	i;

	i = 0;
	while (i < start->philosophers)
	{
		sophers[i].name = i + 1;
		sophers[i].dont_eat = -1;
		sophers[i].semafor = semafor;
		i ++;
	}
}

void	*philo_loop_even_eat(void *args);
void	*philo_loop_even_think(void *args);
void	initialize_philosophers_even(t_start *start, t_philo *sophers, pthread_mutex_t *mut)
{
	int			semafor;
	size_t		i;
	t_arg		*args;
	pthread_t	*thread;

	
	thread = malloc (sizeof(pthread_t) * start->philosophers);
	semafor = 0;
	i = 0;
	initialize_philosophers_mutex(start, sophers, mut);
	initialize_philosophers_else(start, sophers, &semafor);
	while (i < start->philosophers)
	{
		args = malloc(sizeof (t_arg));
		if (args == NULL)
			return ;//error
		args->philo = sophers + i;
		args->start = start;
		if (i % 2 == 1)
			pthread_create(thread + i, NULL, philo_loop_even_eat, args);
		else 
			pthread_create(thread + i, NULL, philo_loop_even_think, args);
		i ++;
	}
	semafor = 1;
	i = 0;
	while (i < start->philosophers)
	{
		pthread_join(thread[i] , NULL);
		i ++;
	}
}

void	*philo_loop_even_eat(void *args)
{
	t_philo	*sopher;
	t_start	*start;


	sopher = ((t_arg*) args)->philo;
	start = ((t_arg*) args)->start;
	while (sopher->semafor == 0)
		usleep(1);
	if (gettimeofday(&sopher->start, NULL) != 0)
		return NULL; //error handle
	if (gettimeofday(&sopher->ate, NULL) != 0)
		return NULL; //error handle
	while(1)
	{
		if (eat_even(sopher, start) == 0)
			return (NULL);
		if (philo_sleep(sopher, start) == 0)
			return (NULL);
		if (think(sopher, start) == 0)
			return (NULL);
		if (*sopher->semafor == 2)
			return (NULL);
		// printf("%lu philoname\n", sopher->name);
	}
}

void	*philo_loop_even_think(void *args)
{
	t_philo	*sopher;
	t_start	*start;


	sopher = ((t_arg*) args)->philo;
	start = ((t_arg*) args)->start;
	while (sopher->semafor == 0)
		usleep(1);
	if (gettimeofday(&sopher->start, NULL) != 0)
		return NULL; //error handle
	if (gettimeofday(&sopher->ate, NULL) != 0)
		return NULL; //error handle
	usleep(0);
	think(sopher, start);
	usleep(10);
	while(1)
	{
		if (eat_even(sopher, start) == 0)
			return (NULL);
		if (philo_sleep(sopher, start) == 0)
			return (NULL);
		if (think(sopher, start) == 0)
			return (NULL);
		if (*sopher->semafor == 2)
			return (NULL);
		// printf("%lu philoname\n", sopher->name);
	}
}





















