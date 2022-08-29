/**
 Commande  reproduire  : ls -l | cut-c2-10 > out
 
 Rsultat  avoir (peut avoir plus ou moins de ligne que cela, mais minimum une, je pense) :
  otal 96
 rwxr-xr-x
 rwxr-xr-x
 rwxr-xr-x
 rw-r--r--
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int i, fd;
    int fdpipe[2];
    char * tokens[300];
    char * command;
    command = (char*) malloc(300);
    char errorMsg[200];
    printf("$ ");
    fgets(command, 200, stdin);
    while(strcmp(command, "exit\n"))
    {
        pipe(fdpipe);
        if(fork() == 0)
        {
            dup2(fdpipe[1], 1);
            close(fdpipe[0]);
            close(fdpipe[1]);
            execlp("ls", "ls", "-l", 0);
        }
        if(fork() == 0)
        {
            dup2(fdpipe[0], 0);
            close(fdpipe[0]);
            close(fdpipe[1]);
            execlp("cut", "cut", "-c2-10", 0);
        }
        wait(0);
        i = 0;
//        tokens[i] = strtok(command," \n");
//        while (tokens[i] != NULL)
//            tokens[++i] = strtok(NULL, " \n");
        if(fork() == 0)
        {
//            if(i > 1 && (strcmp(tokens[i-2],">") == 0))
//            {
                fd = open("out.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
                dup2(fd,1); // dup2 est ncessaire pour mettre ce vers quoi pointe fd dans le fichier vers lequel le contenu doit tre redirig
                close(fd);
//                tokens[i-2] = 0; // Car tokens contient des entiers
//            }
            execvp(tokens[0], tokens);
//            sprintf(errorMsg, "exec <%s>", tokens[0]);
//            perror(errorMsg);
        }
        close(fdpipe[0]);
        close(fdpipe[1]);
        wait(0);
        printf("$ ");
        fgets(command, 299, stdin);
    }
    free(command);
    exit(0);
}
