#pragma warning(disable : 4996)

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
int fl = 0; // a variable indicating whether the desired expression was found

/*
* the function reads the result number from the file
*/
 long long int* value_b_file(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	long long int* mass = malloc(100 * sizeof(long long int));
	if (fscanf(file, "%llu", mass)!=EOF)
	{
		fclose(file);
		return mass;
	}
	else
	{
		fclose(file);
		return 0;
	}

}
 /*
* the function reads a set of digits, between which it is necessary to place the characters in an array from a file
*/
int* value_a_file(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	
	char* mass =(char*) malloc(sizeof(char));
	int mass_int[100];
	int i = 0;
	while (fscanf(file, "%c", mass) != EOF)
	{
		if (mass) {
			mass_int[i] = atoi(mass); //we take the first digit read into the buffer
			i++;
		}
	}
	int* mass_int_1 =(int*) malloc(i * sizeof(int)); 
	for (int j=0;j<i;j++)
	{
		mass_int_1[j] = mass_int[j];
	}
	free(mass);
	
	fclose(file);
	return mass_int_1;

}

/*
* recursive function for iterating through all possible combinations of characters
*/

void function(  int* mass,char* sym,  long long int* result,int m,int length)
{
	double res = 0;
	char zn[5] = { '+','-','*','/','0' };//possible signs(0 means no signs)

	for (int i = 0; i < 5; i++)
	{
		sym[m] = zn[i];
		if (m < length-2) function(mass, sym, result, m + 1, length);
		else
		{
			
			
			sym[m + 1] = '\0';
			long long int* test= malloc(length * sizeof(long long int));
			if (!test)
				exit(-1);
			int flag = 0;
			int count = 1;
			for (int j = 0; j < length; j++) 
			{
				test[j] = mass[j];
			}
			for (int j = length-2; j >= 0; j--) // we merge the digits, that is, we make a two-digit number from two digits if there is no sign between them
			{
				if (sym[j]=='0')
				{
					test[j] = test[j] * pow(10,count) + test[j + 1];
					test[j + 1] = -1; // we fill in the places from which the digit leaves by adding to the number standing left
					flag++;
					count++;
				}
				if (sym[j] != '0')
					count = 1;

			}
			
			double* test_1=(double*)malloc((length -flag)*sizeof(double));
			if (!test_1)
				exit(-1);
			for (int j = 0; j < length -flag; j++)
			{
				test_1[j] = 0;
			}
			int s = 0;
			for (int j = 0; j < length; j++) // getting rid of -1 by creating a new array without it
			{
				if (test[j] != -1)
				{
					test_1[s] = test[j];
					s++;
				}
				
			}
			char* test_sym_1 = (char*)malloc((length -1-flag)*sizeof(char));
			if (!test_sym_1)
				exit(-1);
			s = 0;
			for (int j = 0; j < length-1; j++) // getting rid of the sign indicating the absence of a space by creating a new array without it
			{
				if (sym[j] != '0')
				{
					test_sym_1[s] = sym[j];
					s++;
				}
				
			}
			
			int flag_1 = 0;
			for (int j = length -flag-2; j >= 0; j--) //we perform multiplication or division operations
			{
				if (test_sym_1[j] == '*')
				{
					test_1[j] = test_1[j] * test_1[j + 1];
					test_1[j + 1] = -1; // fill in the places of the digits that are multiplied by the number on the left
					flag_1++;
				}
				if (test_sym_1[j] == '/')
				{
					test_1[j] = test_1[j] / test_1[j + 1];
					test_1[j + 1] = -1; // fill in the places of the digits into which the number on the left was divided
					flag_1++;

					
				}

			}
			double* test_2 = (double*)malloc((length - flag-flag_1) * sizeof(double));
			if (!test_2)
				exit(-1);
			
			s = 0;
			for (int j = 0; j < length -flag; j++) // getting rid of -1 by creating a new array without it
			{
				if (test_1[j] != -1)
				{
					test_2[s] = test_1[j];
					s++;
				}
				
			}
			char* test_sym_2 = (char*)malloc((length-1 - flag-flag_1) * sizeof(char));
			if (!test_sym_2)
				exit(-1);
			s = 0;
			for (int j = 0; j < length -1-flag; j++) // getting rid of * and / in the array by creating a new array without them
			{
				if ((test_sym_1[j] != '*')&& (test_sym_1[j] != '/'))
				{
					test_sym_2[s] = test_sym_1[j];
					s++;
				}
			}
			
			 res =test_2[0];
			for(int j=0;j< length -1-flag-flag_1;j++) // we perform the remaining operations + and -
				switch (test_sym_2[j])
				{
				case 45:
					res -= test_2[j + 1];
					break;
				case 43:
					res += test_2[j + 1];
					break;
				}
			/*
			* freeing up memory
			*/
			free(test_2);
			free(test_1);
			free(test);
			
			
			if (res == *result) // output the resulting expression if the result converged
			{
				 fl=1;
				printf("%d", mass[0]);
				for (int k = 0; k < length-1; k++)
				{
					if(sym[k]!='0')
					printf("%c", sym[k]);
					printf("%d", mass[k+1]);
				}
				printf("\n");
			}
		}
	}
}
/*
* a function that determines the number of digits in the file
*/
int length_f(char* file_name_1)
{
	FILE* file = fopen(file_name_1, "r");

	char* mass = (char*)malloc(sizeof(char));

	int i = 0;
	while (fscanf(file, "%c", mass) != EOF)
	{
		i++;
	}
	fclose(file);
	free(mass);
	return i;
}
/*
* the final function that displays expressions suitable for the working conditions
*/
void calc(char* file_name_1, char* file_name_2)
{
	int length=length_f(file_name_1);
	int* mass_a = value_a_file(file_name_1);
	
	 long long int* mass_b = value_b_file(file_name_2);
	char* sym = malloc(length * sizeof(char));

	int m = 0;
	if(length>=2)
	function(mass_a, sym, mass_b, m,length);
	if (fl == 0)
		printf("0");
}