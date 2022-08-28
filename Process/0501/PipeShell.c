/*
NOM    	: PipeShell.c
CLASSE 	: Process - LaboProcess 05-02
#OBJET  : réservé au Makefile
AUTEUR	: J.C. Jaumain, 07/2011
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
    int fdpipe1[2];//,fdpipe1[2];
	char command[257];
	printf("Commande ? ");
	fgets(command,256,stdin);
	while (strcmp(command,"exit\n"))
	{
        pipe(fdpipe1);
        if(fork() == 0)
        {
            dup2(fdpipe1[1], 1);
            close(fdpipe1[0]);
            close(fdpipe1[1]);
            execlp("ps", "ps", "aux", 0);
        }
        if(fork() == 0)
        {
            dup2(fdpipe1[0], 1);
            close(fdpipe1[0]);
            close(fdpipe1[1]);
            execlp("grep", "grep", "root", 0);
        }
        close(fdpipe1[0]);
        close(fdpipe1[1]);
        while(wait(0)>0);
        printf("Commande ? ");
        fgets(command, 256, stdin);
	}	
	exit(0);
}
