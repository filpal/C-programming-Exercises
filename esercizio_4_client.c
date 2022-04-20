/*
 ============================================================================
Creiamo un server di lunghezza fissa, il client invia messaggi di lunghezza fissa al server,
crea una pipe la apre in lettura e poi c’è un ciclo che legge il messaggio della
pipe  e poi il messaggio finisce con end
 ============================================================================
 */



// PROCESSO CLIENT

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define FIFOFILENAME "pipe_fifo"
#define SIZE 80

int main(int argc, char *argv[]) {
  FILE *fp;
  char myOutput[80];

 for (int i=0; i<3; i++)
 {
    if ((fp=fopen(FIFOFILENAME,"w"))== NULL) {
        printf("c'e' stato un errore mentre tentavo di aprire la pipefile");
        exit(1);
    }
    else
    {

        scanf("%s", myOutput);
        fprintf(fp, "%s\n", myOutput); fflush(fp);
    }
  }

 fprintf(fp, "\0"); fflush(fp);
 fclose(fp);

  return 0;
}
