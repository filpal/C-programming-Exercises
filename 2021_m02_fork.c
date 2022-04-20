/*
 * Si realizzi un programma “fork2.c” che possa ricevere come
input un numero intero immesso da tastiera. A tale numero, il
processo figlio creato somma 20, mentre il processo padre somma
10.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	int valore, pid;

	if (argc < 2)
		{
		fprintf(stderr,"Uso: %s <numero intero>\n",argv[0]);
		exit(-1);
	}
	else
		valore = atoi(argv[1]);

	if((pid=fork())<0) 		/*Creazione processo figlio*/
	{
		perror("fork");
		exit(-1);
	}

	switch (pid)
	{
	case -1:
		printf("Errore");
		break;

	case 0:					/* Processo figlio */
		valore += 10;
		printf("[F] mio pid: %d: mio padre ha pid: %d; somma finale= %d \n", getpid(), getppid(), valore );
		break;

	default:				/* pid > 0 : Processo padre */
		 valore += 20;
		 printf("[P] mio pid: %d: mio figlio ha pid: %d; somma finale= %d \n", getpid(), pid, valore );

	}
	return 0;
}