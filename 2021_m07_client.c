/*
 ============================================================================
Si vuole realizzare un’applicazione in ambiente UNIX basata su uno schema client-server.
L’applicazione deve essere costituita da due processi (client e server, non necessariamente parenti):
 a. il client è un programma che prevede una sintassi di invocazione del tipo <client com fileout>.
 	 Il client interagisce con il server per richiedere l’esecuzione di un servizio
 	 (l’esecuzione del comando com) con ridirezione sul file fileout;
 b. il server è un programma (che non prevede argomenti) che, una volta ricevuti dal client com e fileout,
 	 provvede all’esecuzione di com con ridirezione su fileout.
 ============================================================================
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 40

int main(int argc, char **argv)
{
	FILE * fd;

	if (argc != 3){
		printf("Uso: nomeprogramma <comando> <nomefileInput>\n");
		exit(-1);
	}

	if ((fd=fopen("server.in", "w+"))<0)
	{
		perror("client-open fifo in: ");
		exit(-1);
	}

	fprintf(fd,"%s %s", argv[1], argv[2]);

	fclose(fd);

}