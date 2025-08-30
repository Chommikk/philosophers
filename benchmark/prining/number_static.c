
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
void	print_died(int count)
{
	char				str[100];
	static const unsigned long long i = 0x6f77206f6c6c6568;
	static const unsigned long long j = 0xa646c72;

	/*
	str[8] = 'r';
	str[9] = 'l';
	str[10] = 'd';
	str[11] = '\n';
	unsigned long long	i;
	memmove(&i, str + 8,8);
	printf("sizeof() %lu\n", sizeof(unsigned long long));
	*/
	*((unsigned long long*)str) = i;
	*((unsigned long long*)(str + 8)) = j;
}
int main()
{
	int i = 0;
	clock_t start = clock();
	while(i < 10000000)
	{
		print_died(i);
		i ++;
	}
	clock_t end = clock();
	double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Execution time: %f seconds\n", time_taken);
    return 0;
}
