/*
 ============================================================================
Esercitazione su creazione e terminazione thread scrivere un programma che crea
un thread e attende la terminazione dello stesso , il thread scriverà a video
numeri da 0 a 10 per un tot di tempo
 ============================================================================
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void stampa (){

	while (1)
	{
		for (int i = 0;i<10; i++)
			printf("numero %d\n", i);
	}

}

int main(void) {

	pthread_t th1;
	pthread_create(&th1, NULL, (void *)stampa, (void *)1);
	sleep(1);
	pthread_kill(th1,(void *) NULL);
	printf ("termine programma\n");
	return 0;

}
