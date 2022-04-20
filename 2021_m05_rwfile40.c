/*
 ============================================================================
Scrivere un programma C che prenda come parametro due nomi di file inputFile
ed outputFile (controllare che il numero di argomenti passati sia corretto):
il programma dovr� generare un processo figlio, PF che aprir� il file inputFile
copiando i primi 40 caratteri di inputFile in outputFile aggiungendo alla fine
il proprio PID;
il padre attender� il figlio ed aggiunger� ad outputFile il proprio PID.
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> /*wait*/


int main(int argc, char **argv) {

	FILE * in_fd, * out_fd;
	int  pid;

	char buf[60];

	if (argc != 3)
	{
		printf(" Uso: %s <inputFile> <outputFile> \n", argv[0]);
		exit (1);
	}
	/* Apertura file outputFile*/
	if ((out_fd=fopen(argv[2], "w+")) == NULL)
	{
		printf("Errore apertura outputFile %s\n:",argv[2]);
		exit(1);
	}
	if((pid=fork())<0) /*Creazione processo figlio*/
	{
		perror("Error nella esecuzione della fork");
		exit(1);
	}
	else if (pid == 0) 				/*Processo figlio*/
	{ 								/* Apertura file inputFile*/
		if ((in_fd = fopen(argv[1],"r")) == NULL)
		{
			printf("Errore apertura inputFile da leggere %s\n:",argv[1]);
			exit(-1);
		}
								/*legge i primi 40 caratteri*/
		fgets(buf, 41, in_fd);	/*fgets inserisce a fine stringa il "newline caracter"
								/*scrive i primi 40 caratteri*/
		fprintf(out_fd,"%s", buf);

		fprintf(out_fd,"\nPID figlio:%d\n ", getpid());
		fclose(in_fd);
		fclose(out_fd);
		exit(0);
	}
	else
		{ 					/*Processo Padre*/
							/*Attende che il figlio finisca di scrivere*/
			wait(NULL);

			printf("Inizio processo padre\n");

			/*scrive i PID caratteri*/
			out_fd = fopen(argv[2], "a+");
			fprintf(out_fd,"PID padre: %d\n", getpid());
			printf("Fine processo padre\n");
			fclose(out_fd);
		}
	return 0;
}