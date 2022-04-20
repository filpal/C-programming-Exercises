/*
 ============================================================================
Si vuole realizzare un programma in C che creano nproc processi figli che
eseguono un certo numero di iterazioni, si attende quindi la loro terminazione
stampando la condizione di terminazione l'exit status e l'eventuale segnale
che ha terminato il processo.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int i, pid[5];

	for (i=0;i<5;i++)
	{
		pid[i] = fork();
		switch (pid[i])
		{
			case -1:
				//error usciamo:
			    break;
			case 0:
			// figlio
				printf("[F] figlio: %d, con pid %d\n", i, getpid());fflush(stdout);
				printf("[F] figlio: %d in attesa di %d secondi\n", i, ((rand()%5)+i));fflush(stdout);
				sleep((rand() %5)+i);
				printf("[F] figlio: %d terminato dopo %d\n", i,((rand()%5)+1));fflush(stdout);
				exit(1);
			default:
				printf("[P]: %d; padre del processo: %d\n", getpid(), pid[i]);fflush(stdout);
				break;
		}

	}

	for(i=0;i<5;i++)
	  {
	  int status;
	  waitpid(pid[i], &status, 0);
	    printf("Terminato processo %d con status %d\n",i, WEXITSTATUS(status));fflush(stdout);
	  }


}