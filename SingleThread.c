#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include "primedecompose.h"

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp
#define MAX_FACTORS	1024

// Globals
mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors! 

void task(char* prime){
	clock_t begin = clock(); //start time of thread
	mpz_t n;
	int i, l;
	mpz_init_set_str(n, prime, 10);
	l = decompose(n, dest);

	for(i=0; i < l; i++) 
	{
		gmp_printf("%s%Zd", i?" * ":"", dest[i]);
		mpz_clear(dest[i]);
	}

	clock_t end = clock(); //end time of thread
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nspent: %lf secs\n",time_spent);
}

int main(int argc, char **argv) 
{
	clock_t begin = clock(); //start time of thread
  	if(argc != 3) 
	{
		//get large primes from http://www.primos.mat.br/50mi_en.html
		puts("Usage: ./pdec <number to be factored> <number of time to repeat task>");
		return EXIT_SUCCESS;
  	}
	char* arg1 = argv[1];
    int arg2 = atoi(argv[2]);

    for(int i=0;i<arg2;++i){
  	    task(arg1);
    }

	clock_t end = clock(); //end time of thread
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTotal spent: %lf secs\n",time_spent);
  	return EXIT_SUCCESS;
}


