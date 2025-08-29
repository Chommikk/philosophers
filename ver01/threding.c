#include <pthread.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <sys/time.h>

typedef struct	s_mut
{
	pthread_mutex_t	lock;
	int				counter;
}	t_mut;

void	*precision_check(void *arg)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	size_t			i;

	i = 0;
	if (gettimeofday(&start, NULL) != 0)
		return (NULL); //error handle
	while (i < 20000)
		i++;
	while (time < 200)
	{
		usleep(1);
		if (gettimeofday(&end, NULL) != 0)
			return NULL; //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	}
	printf("%lu time spend\n", time);
	return (NULL);
}

void	*performance_check(void *arg)
{
	struct timeval	start;
	struct timeval	end;
	size_t			time;
	size_t			i;

	i = 0;
	if (gettimeofday(&start, NULL) != 0)
		return (NULL); //error handle
	while (i < 200)
	{
		if (gettimeofday(&end, NULL) != 0)
			return NULL; //error handle
		time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
		i ++;
	}
	return (NULL);
}

void	*empty(void *arg)
{
	return (NULL);
}

void	*mutex_test(void *arg)
{
	int i = 0;
	t_mut	*data = (t_mut*) arg;

	pthread_mutex_lock(&data->lock);
	while(i < 50)
	{
		printf("%i", data->counter);
		i++;
	}
	printf("Hello from thread %i\n", data->counter);
	data->counter ++;
	pthread_mutex_unlock(&data->lock);
	return (NULL);
}



void	*hello_nbr(void *arg)
{
	int i;
	i = 0;
	(**(int **)arg)++;
	while(i < 50)
	{
		printf("%i", **(int **)arg);
		i++;
	}
	printf("Hello from thread %i\n", (**(int  **)arg));
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	*thread;
	size_t		i;
	t_mut		data;
	struct timeval	start;
	struct timeval	end;
	size_t		amount;

	amount = ft_atoi(argv[1]);

	/*
	data.counter = 0;
	if (pthread_mutex_init(&data.lock, NULL) != 0) {
		perror("Mutex init failed");
		return 1;
	}
	*/

	thread = ft_calloc(sizeof(pthread_t), ft_atoi(argv[1]));

	i = 0;
	if (gettimeofday(&start, NULL) != 0)
		return (0); //error handle
	while (i < amount)
	{
		if (pthread_create(thread + i, NULL, precision_check, &data) != 0)
			return (0);
		i ++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(thread [i], NULL) != 0)
			return (0);
		i ++;
	}
	if (gettimeofday(&end, NULL) != 0)
		return (0); //error handle
	// size_t	time = (end.tv_sec - start.tv_sec) * 1000UL + (end.tv_usec - start.tv_usec) / 1000;
	// printf("%lu\n", time);
	return (0);

}
