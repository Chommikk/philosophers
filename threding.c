#include <pthread.h>
#include <stdio.h>
#include "../libft/libft.h"

void	*hello_nbr(void *arg)
{
	printf("Hello from thread %s\n", (char *)arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	*thread;
	size_t		i;

	thread = ft_calloc(sizeof(pthread_t), ft_atoi(argv[1]));

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(thread + i, NULL, hello_nbr, ft_itoa(i)) != 0)
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
	return (0);

}
