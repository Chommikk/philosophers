
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
void	print_died(int count)
{
	char				str[100];

	str[0] = 'h';
	str[1] = 'e';
	str[2] = 'l';
	str[3] = 'l';
	str[4] = 'o';
	str[5] = ' ';
	str[6] = 'w';
	str[7] = 'o';
	str[8] = 'r';
	str[9] = 'l';
	str[10] = 'd';
	str[11] = '\n';
}
int main(int  argc, char **argv)
{
	int i = 0;
	clock_t start = clock();
	while(i < 10000000)
	{
		print_died(i + argc);
		i ++;
	}
	clock_t end = clock();
	double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Execution time: %f seconds\n", time_taken);
    return 0;
}
