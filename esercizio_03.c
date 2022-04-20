/*
 ============================================================================
Vogliamo creare 2 nuovi thread, uno che stampa X e uno che stampa Y, e
anziché stampare caratteri all’infinito, vogliamo che ciascun thread stampa
un numero fisso di caratteri e poi esce ritornando alla funzione thread,
entrambi i thread utilizzano la stessa funzione
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * mystampa (char *r)
{
	for (int i=0; i<10; i++) {
		fprintf(stderr,"messaggio %s\n",  r);
	}
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t prod1, prod2;
	pthread_create(&prod1, NULL, mystampa, "hello X");
	pthread_create(&prod2, NULL, mystampa, "hello Y");
	pthread_join(prod1, NULL);
	pthread_join(prod2, NULL);
}