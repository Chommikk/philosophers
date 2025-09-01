#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
void	print_died(int count)
{
	char				str[100];
	unsigned long long	i;
	unsigned long long	j;

	// has taken a fork\n
	memmove(&i, " is slee", 8);
	printf("%llx\n", i);
	*((unsigned long long*)str) = i;
	bzero(&j, 8);
	memmove(&j, "ping\n", 5);
	printf("%llx\n", j);
	*((unsigned long long*)(str + 8)) = j;
	// *(unsigned long long*)(str) = 0x6974616520736920;
	// *(unsigned long long*)(str + 8) = 0xa676e;
	write(1, str, 13);
}
int main()
{
	int i = 0;
	clock_t start = clock();
	print_died(i);
	/*
	while(i < 10000000)
	{
		print_died(i);
		i ++;
	}
	*/
	clock_t end = clock();
	double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Execution time: %f seconds\n", time_taken);
    return 0;
}
