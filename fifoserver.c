#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define FIFOFILENAME "myfifo"
#define SIZE 80


int main(int argc, char *argv[]) {
	FILE *fp;
	char buf[80];
	umask(0); // crea la FIFO
	mknod(FIFOFILENAME, S_IFIFO|0600,0);
	int count = 0;
	while(count < 3) {
		fp=fopen(FIFOFILENAME,"r");
		fgets(buf,SIZE,fp);
		printf("Ricevuto: %s\n",buf);
		fclose(fp);
		count++;

	}
	exit(0);
}