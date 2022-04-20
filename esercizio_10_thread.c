/*
 ============================================================================
Vogliamo scrivere un programma che crea 4 thread, vengono passati tramite una
struttura 2 parametri, il numero del thread e un messaggio
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


struct param
{
 int pid;
 char msg[12];
};

typedef struct param nuovoTipo;


int stampa (void *a)   /// a è di tipo puntatore a void; b è di tipo nuovoTipo
{
	nuovoTipo *b;
	b=(nuovoTipo*)a;
	printf("sono il thread N. %d, porto il messaggio \"%s\"\n", b->pid, b->msg);
	return 0;
}

int main(void) {

	pthread_t th[4];
	nuovoTipo *a;
	 a=(nuovoTipo *)malloc(sizeof(nuovoTipo));
	 strcpy(a->msg, "Buongiorno");
	 for (int i =0; i<4; i++){
		 a->pid = i;
		 pthread_create(&th[i],NULL,(void*)stampa,(void*) a);
		 pthread_join(th[i],NULL);
	 }
	 return 0;

}

