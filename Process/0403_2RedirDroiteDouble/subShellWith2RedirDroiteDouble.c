/**
 Créer un subshell qui prend en compte l'opérateur "2>>", soit la redirection dans un fichier de la sortie d'erreur
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
        i = 0;
        tokens[i] = strtok(command," \n");
        while (tokens[i] != NULL)
            tokens[++i] = strtok(NULL, " \n");
        if(fork() == 0)
        {
            if(i > 1 && (strcmp(tokens[i-2],"2>>") == 0))
            {
                fd = open(tokens[i-1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                dup2(fd,2); // dup2 est nécessaire pour mettre ce vers quoi pointe fd dans le fichier vers lequel le contenu doit être redirigé : 0 = in, 1 = out, 2 = err
                close(fd);
                tokens[i-2] = 0; // Car tokens contient des entiers
            }
            execvp(tokens[0], tokens);
            sprintf(errorMsg, "exec <%s>", tokens[0]);
            perror(errorMsg);
        }
        wait(0);
        printf("$ ");
        fgets(command, 299, stdin);
    }
    free(command);
    exit(0);
}
