/*
 ============================================================================
Scrivere un programma C che prenda come parametro un file
inputFile (controllare che il numero di argomenti passati sia
corretto). Il programma dovrà aprire tale file, creare un processo
figlio, PF che scriverà nel file inputFile una stringa inserita da
tastiera. Il padre attenderà il figlio e visualizzerà sul video il
contenuto del file inputFile

 ============================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> /*wait*/

int main(int argc, char **argv) {

	FILE * fd;
	int pid, status;
	char st1[256];
	char st2[256];

	if (argc < 2)
	{
		fprintf(stderr,"Uso: %s <nomefileInput>\n",argv[0]);
		exit(1);
	}
	/* Apertura del file in scrittura */
	if ((fd=fopen(argv[1], "w+")) == NULL)
	{
		perror("error opening argv[1]");
		exit(1);
	}

	if((pid=fork())<0) /*Creazione processo figlio*/
	{
		perror("Errore nella creazione della fork");
		exit(-1);

	} else if (pid==0) 			/* Processo figlio */
	{
		printf("[F] Introduci una stringa e premi [Enter]\n");
		fgets(st1, sizeof(st1), stdin);
		fprintf(fd,"%s", st1); /* Il figlio eredita il descrittore fd dal padre */
		fclose(fd);
		exit(0);

	} else
	{						/* pid > 0 : Processo padre */
		wait(&status);		/* Attesa della terminazione del figlio */
		if ( WIFEXITED(status) )
			printf("[P]: figlio ha terminato con status %d.\n",WEXITSTATUS(status));
		else
			printf("[P]: figlio ha terminato in modo anomalo.\n");

		 fd = fopen(argv[1],"r");
		   while(1) {
			   fgets(st2,sizeof(st2),fd);
			   if( feof(fd) ) break;
		       printf("[P]: %s", st2);
		   }
		   fclose(fd);

	}
	return 0;
}