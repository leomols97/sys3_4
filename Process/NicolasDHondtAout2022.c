/**
 Commande à reproduire dans un shell qui l'exécute, quelle que soit la commande que l'on lui donne : ls -R / >out 2>&1
 2>&1 redirige stderr sur stdout
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
    char * tokens[300];
    char * command;
    command = (char*) malloc(300);
    char errorMsg[200];
    printf("$ ");
    fgets(command, 200, stdin);
    while(strcmp(command, "exit\n"))
    {
        if(fork() == 0)
        {
            execlp("ls", "ls", "-R", "/Users/leopoldmols/Desktop/ESI/2-3eme/Quadri2/SYSG4", 0);
            sprintf(errorMsg, "exec <%s>", tokens[0]);
            perror(errorMsg);
        }
        wait(0);
        i=0;
        tokens[i]=strtok(command, " \n");
        while (tokens[i] != NULL)
            tokens[++i]=strtok(NULL, " \n");
        if (fork()==0)
        {
//            if ((i>1) && (strcmp(tokens[i-2],">")==0))
//            {
                fd=open("out.txt",O_WRONLY|O_CREAT|O_TRUNC ,0644);
                dup2(fd,1);
                close(fd);
                tokens[i-2]=0;
//            }
            execvp(tokens[0],tokens);
            perror("exec");
        }
        wait (0);
        printf("$ ");
        fgets(command, 256, stdin);
    }
    free(command);
    exit(0);
}
