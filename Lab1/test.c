#include <stdio.h>
#include <assert.h>
int main()
{
	int a = 2;
	int b = 3;
	int d = a>b?1:-1;
	printf("%d\n", d);
	d = 0;
	assert(d);
}