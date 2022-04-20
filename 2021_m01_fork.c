/*
 * Si realizzi un programma C “fork1.c” che stampi a video il pid del
processo che lancerà un fork e dopo l’esecuzione (fork), sia in grado di
identificare i processi genitore e figlio con i relativi pid testando i
valori di ritorno da fork.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

	int status, pid = fork();

	switch(pid)
	{
		case -1:
			printf("Errore nella creazione della fork");
			exit(-1);
		case 0:
			printf("[F]il pid di mio padre:%d\n",getppid());
			printf("[F]il mio pid: %d\n",getpid());
			sleep(3);
			printf("[F]Sto per terminare\n");
			exit(0);
		default:
			printf("[P]il mio pid: %d\n", getpid());
			printf("[P]il pid di mio figlio: %d\n", pid);
			printf("[P]Mi metto in attesa\n");
			wait(&status);
			printf("[P]Finito l'attesa di mio figlio %d. Exit %d\n", pid, status);
			break;
	}
	return 0;
}