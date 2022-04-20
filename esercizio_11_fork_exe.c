/*
============================================================================
Scrivere un programma che prenda come argomento un programma eseguibile ed i
suoi eventuali argomenti e lancia il programma attendendo la sua terminazione
============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int argc,char **argv)
{
	pid_t pid;

	if(!(argc>1)) {
		fprintf(stderr,"Uso del programma: %s <comando> <parametri>\n", argv[0]);
		exit(1);
	}
	pid=fork();

	switch(pid) {
	case -1:
		perror("Errore nella chiamata a fork");
		exit(2);
	case 0:   //figlio
		execvp(argv[1],&argv[1]);
		perror("Errore nella chiamata a execvp");
		exit(3);
	default:
		waitpid(pid,NULL,0);
		return 0;
	}
}
