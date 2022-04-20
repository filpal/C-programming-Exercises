/*
 ============================================================================
Creiamo un server di lunghezza fissa, il client invia messaggi di lunghezza fissa al server,
crea una pipe la apre in lettura e poi c’è un ciclo che legge il messaggio della
pipe  e poi il messaggio finisce con end
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define FIFOFILENAME "pipe_fifo"
#define SIZE 8




int main(int argc, char *argv[]) {

	FILE *fp = NULL;
    umask(0);
    mknod(FIFOFILENAME, S_IFIFO|0666,1);

  //(mkfifo(FIFOFILENAME, S_IFIFO | 0644) == FAIL && errno != EEXIST)

  char buf[SIZE];

  do {
    fp=fopen(FIFOFILENAME,"r");
    if ((fp!=NULL))

    {
        fgets(buf,SIZE,fp);
        printf("stringa ricevuta %s", buf);
        if (buf == "\0")
        	strcmp( buf, "\0") == 0


        	{
        		fclose(fp);
        		exit(0);
        	}
        fclose(fp);
    }
    else
    {
        perror("c'e' stato un errore mentre tentavo di aprire la pipefile");
    }
  } while(fp!=NULL);


  return 0;
}


