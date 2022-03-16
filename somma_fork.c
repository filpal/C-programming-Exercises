
Si realizzi un programma “fork2.c” che possa ricevere come
input un numero intero immesso da tastiera. A tale numero, il
processo figlio creato somma 20, mentre il processo padre somma
10.  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	int valore = 0;
	if (1 < argc)
		valore = atoi (argv[1]);
	int pid = fork();

	switch (pid)
	{
	case -1:
		printf("Errore");
		break;

	case 0:
		valore += 10;
		printf("Processo figlio con pid: %d: somma finale %d \n", getpid(), valore );
		break;

	default:
		 valore += 20;
		 printf("Processo padre con pid: %d: somma finale %d \n", getppid(), valore );

	}

}