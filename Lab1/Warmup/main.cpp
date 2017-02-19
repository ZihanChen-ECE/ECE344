/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: zihan
 *
 * Created on January 13, 2017, 12:18 PM
 */

#include <cstdlib>
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
	
	int Value = 0;

	for (int ii = 0; ii < Num_len; ii++)
	{ 
		if (argv[1][ii]<'0' || argv[1][ii]>'9')
		{
			printf("Hun?\n");
			return -1;
		}
		Value += ii * pow(10,Num_len-ii-1);
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


