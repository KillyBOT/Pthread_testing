#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct test_struct{
	int start, stop;
	int threadNum;
};

int counter;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


void *add_numbers_function(void *ptr);

int main(){
	pthread_t pt_1, pt_2;
	struct test_struct s1, s2;

	counter = 0;

	s1.start = 0;
	s1.stop = 20;
	s1.threadNum = 1;

	s2.start = 10;
	s2.stop = 30;
	s2.threadNum = 2;

	int pret1, pret2;

	pret1 = pthread_create(&pt_1, NULL, add_numbers_function, (void*) &s1);
	pret2 = pthread_create(&pt_2, NULL, add_numbers_function, (void*) &s2);

	pthread_join(pt_1, NULL);
	pthread_join(pt_2, NULL);

	printf("Thread 1 returned %d\n", pret1);
	printf("Thread 2 returned %d\n", pret2);
}

void *add_numbers_function(void *ptr){

	struct test_struct ts;

	ts.start = ((struct test_struct*)ptr)->start;
	ts.stop = ((struct test_struct*)ptr)->stop;
	ts.threadNum = ((struct test_struct*)ptr)->threadNum;

	pthread_mutex_lock(&mutex1);

	for(int n = ts.start; n <= ts.stop; n++){
		counter += n;
		printf("Thread [%d]:\tCounter: [%d]\n", ts.threadNum, counter);
	}

	pthread_mutex_unlock(&mutex1);
}