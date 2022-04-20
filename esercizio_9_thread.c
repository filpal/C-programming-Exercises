/*
 ============================================================================
Scriviamo un programma che crea 2 thread indipendenti ciascuno dei quali crea
una funzione e stampa a video il messaggio del proprio thread (thread 1 e thread2)
 ============================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void stampa (void * i) {
	printf("Sono il thread N. %d\n", i);
	printf("Sono il thread N. %d\n", pthread_self());
}

int main(void) {

pthread_t t1, t2;

	pthread_create(&t1, NULL, (void *)stampa, (void *)1);
	pthread_create(&t2, NULL, (void *)stampa, (void *)2);
	sleep(1);
	//pthread_join(t1, NULL); //per attendere la fine dei thread
	//pthread_join(t2, NULL);

	return 0;
}
