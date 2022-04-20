/*
 =================================================================
esame gennaio 2022: esercizio 2 vogliamo creare un programma che
crea un tread e stampa infinite X sullo standard
error e dopo la chiamata del tread ,il principale (main) stampa
infinite Y sullo standard error
 =================================================================
fatto con i processi , ma meglio con i thread
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int pid;
	if ((pid = fork()) == NULL   )
		fprintf(stdout,"Errore nella creazione del processo figlio");fflush();
		perror ();
	if (pid != 0)
	{				// figlio
		while (1)   //ciclo infinito
		{
			fprintf(stderr, "FIGLIO-X-\n");  //sterror non bufferizzato, stampa direttamente
		}
	}
	else {			//padre
		while (1)
		{
			fprintf(stderr, "PADRE-Y-\n");
		}
	}
}
