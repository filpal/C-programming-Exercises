/*
 * Scrivere un programma C in cui il processo di comunicazione tra padre e figlio
 * è gestito da una pipe. Il programma dovrà quindi creare la pipe, generare il processo figlio PF
 * che scriverà  nella pipe una stringa inserita da tastiera. Il processo padre, visualizzerà
 * sul video il contenuto della pipe
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/wait.h>

enum {BUF_SIZE = 128};

int main(int argc, char *argv[]) {
    int pipe_fd[2];
    int status;
    char buf[BUF_SIZE];
    ssize_t numRead;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    switch (fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            if (close(pipe_fd[1]) == -1) {
                perror("close - parent");
                exit(EXIT_FAILURE);
            }

            sleep(3);
            numRead = read(pipe_fd[0], buf, BUF_SIZE);
            write(STDOUT_FILENO, buf, numRead);

            write(STDOUT_FILENO, "\n", 1);
            if (close(pipe_fd[0]) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
            _exit(EXIT_SUCCESS);

        default:
            if (close(pipe_fd[0]) == -1) {
                perror("close - parent");
                exit(EXIT_FAILURE);
            }

            if (write(pipe_fd[1], argv[1], strlen(argv[1])) != strlen(argv[1])) {
                perror("write - partial/failed write");
                exit(EXIT_FAILURE);
            }

            if (close(pipe_fd[1]) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }

            wait(NULL);
            exit(EXIT_SUCCESS);
    	}
}
/*
int main() {
  int fd[2];

  pipe(fd); //crea la pipe
  if (fork() == 0) {
    char *phrase = "prova a inviare questo!";

    close(fd[0]);                         // chiude in lettura
    printf("[F] : scrivo nella pipe %d bytes: '%s' \n",strlen(phrase)+1, phrase);
    write(fd[1],phrase,strlen(phrase)+1); // invia anche 0x00
    close(fd[1]);                         // chiude in scrittura
  }
  else
  {
    char message[100];
    //memset(message,0,100);
    int bytesread;
    close(fd[1]);                         //chiude in scrittura
    bytesread = read(fd[0],message,128);
    printf("[P]: ho letto dalla pipe %d bytes: '%s' \n",bytesread,message);
    close(fd[0]);                         // chiude in lettura
  }
}

*/
