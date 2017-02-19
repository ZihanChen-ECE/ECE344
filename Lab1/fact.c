#include <stdio.h>
#include <string.h>
#include <math.h>

int fact(int num);

int main(int argc, char ** argv)
{
	int N = argc;
	if (N != 2)
	{
		printf("Hun?\n");
		
		return -1;
	}

	//char *Number = argv[1];
	//printf("%s\n",argv[1]);
	int	Num_len = strlen(argv[1]);
	//printf("Num_len:%d\n", Num_len);
	int Value = 0;
	//for (int ii = 0; ii < Num_len; ii++)
	//{
	//	printf("%d\n",argv[1][ii]-'0'); 
	//}

	for (int ii = 0; ii < Num_len; ii++)
	{ 
		if (argv[1][ii]<'0' || argv[1][ii]>'9')
		{
			printf("Hun?\n");
			return -1;
		}
		Value += (argv[1][ii]-'0') * pow(10,Num_len-ii-1);
	}
	if(Value > 12)
	{
		printf("Overflow\n");
		return -1;
	}

	printf("%d\n", fact(Value));


}

int fact(int num)
{
	if(num == 1)
		return 1;
	return num*fact(num-1);
}








