#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pthread.h>
#include <time.h>
#include "primedecompose.h"

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp
#define MAX_FACTORS	1024

// Globals
mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors! 

/*------------ Mutex Variables ---------------------*/
pthread_mutex_t printfLock = PTHREAD_MUTEX_INITIALIZER;

void task(char* prime){
	struct timespec start, finish;
	clock_gettime(CLOCK_MONOTONIC, &start);
	double elapsed;
	mpz_t n;
	int i, l;
	mpz_init_set_str(n, prime, 10);
	l = decompose(n, dest);

	for(i=0; i < l; i++) 
	{
		pthread_mutex_lock(&printfLock);
		gmp_printf("%s%Zd", i?" * ":"", dest[i]);
		pthread_mutex_unlock(&printfLock);
		mpz_clear(dest[i]);
	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	pthread_mutex_lock(&printfLock);
	printf("\nspent: %lf secs\n",elapsed);
	pthread_mutex_unlock(&printfLock);
}

int main(int argc, char **argv) 
{
  	if(argc != 2) 
	{
		//get large primes from http://www.primos.mat.br/50mi_en.html
		puts("Usage: ./pdec <number to be factored>");
		return EXIT_SUCCESS;
  	}
	struct timespec start, finish;
	clock_gettime(CLOCK_MONOTONIC, &start);
	double elapsed;
	char* arg1 = argv[1];
	pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
	pthread_create(&thread1, NULL, task, arg1);
 
	pthread_join(thread1, NULL);

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("\nTotal spent: %lf secs\n",elapsed);
  	return EXIT_SUCCESS;
}


