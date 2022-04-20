#include <stdio.h>
#include <stdlib.h>
#define FIFOFILENAME "myfifo"

int main(int argc, char *argv[])
{
	FILE *fp;
	if (argc!=2)
	{
		printf("Uso: fifoclient <stringa>\n");
		exit(-1);
	}
	if ((fp=fopen(FIFOFILENAME,"w"))==NULL)
	{
		perror("fopen() fallita");
		exit(-2);
	}
	fputs(argv[1],fp);
	fclose(fp);
	exit(0);
}s