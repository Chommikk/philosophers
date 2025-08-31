#include "philosophers.h"
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

size_t	get_time_in_size_t(void)
{
	struct timeval	t;
	size_t			i;

	gettimeofday(&t, NULL);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (i);
}

int main()
{
	printf("%lu\n", get_time_in_size_t());
	printf("%lu\n", ULONG_MAX);
}
