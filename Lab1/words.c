# include "stdio.h"
//# include "strlib.h"

int main(int argc, char ** argv)
{
	int N = argc;
	int ii;
	for(ii = 1; ii<N; ii++)
	{
		printf("%s\n", argv[ii]);
	}
}