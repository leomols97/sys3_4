/*
NOM : subShell.c
CLASSE : Process - LaboProcess 02-02 #OBJET : rserv au Makefile
AUTEUR : J.C. Jaumain , 07/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
	int i;
	char command[200];
	char errorMsg[200];
	char * tokens[300];
	printf("$ ");
	fgets(command,199, stdin);
	while(strcmp(command, "exit\n"))
	{
		i=0;
		tokens[i] = strtok(command, " \n");
		while(tokens[i] != NULL)
			tokens[++i] = strtok(NULL, " \n");
		if(fork() == 0)
		{
			execvp(tokens[0], tokens);
			sprintf(errorMsg, "La commande %s n'a pas pu être exécutée", tokens[0]);
			perror(errorMsg);
		}
		wait(0);
		printf("$ ");
		fgets(command,199, stdin);
	}
	exit(0);
}
