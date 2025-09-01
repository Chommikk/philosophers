#include <unistd.h>
#include "../../var02/philosophers.h"
void	print_fork(t_philo *data, size_t passed)
{
	printf("%lu %i has taken a fork\n", passed, data->name);
	fflush(stdout);
}

int main()
{
	t_philo sopher;
	int i = 0;
	sopher.name = 150;
	clock_t start = clock();
	while(i < 1000)
	{
		print_fork(&sopher, i);
		i ++;
	}
	clock_t end = clock();
	double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Execution time: %f seconds\n", time_taken);
    return 0;
}
