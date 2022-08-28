#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
    int fdpipe1[2], fdpipe2[2];
	char command[257];
	printf("Commande ? ");
	fgets(command,256,stdin);
	while (strcmp(command,"exit\n"))
	{
        pipe(fdpipe1);
        pipe(fdpipe2);
        if(fork() == 0)
        {
            dup2(fdpipe1[1], 1);
            close(fdpipe1[0]);
            close(fdpipe1[1]);
            close(fdpipe2[0]);
            close(fdpipe2[1]);
            execlp("ps", "ps", "aux", 0);
        }
        if(fork() == 0)
        {
            dup2(fdpipe1[0], 0);
            dup2(fdpipe2[1], 1);
            close(fdpipe1[0]);
            close(fdpipe1[1]);
            close(fdpipe2[0]);
            close(fdpipe2[1]);
            execlp("grep", "grep", "root", 0);
        }
        if(fork() == 0)
        {
            dup2(fdpipe2[0], 0);
            close(fdpipe1[0]);
            close(fdpipe1[1]);
            close(fdpipe2[0]);
            close(fdpipe2[1]);
            execlp("wc", "wc", "-l", 0);
        }
        close(fdpipe1[0]);
        close(fdpipe1[1]);
        close(fdpipe2[0]);
        close(fdpipe2[1]);
        while(wait(0)>0);
        printf("Commande ? ");
        fgets(command, 256, stdin);
	}	
	exit(0);
}
