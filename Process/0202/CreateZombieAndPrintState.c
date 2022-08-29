/*
NOM : Zombie.c
CLASSE : Process - LaboProcess 02-02 #OBJET : réservé au Makefile
AUTEUR : J.C. Jaumain , 07/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
    char spid [100];
    int pid;
    if ((pid = fork()) == 0)
//        fork(); // Manière 1 d'éviter un zombie
        exit(0);
    printf("Le fils est maintenant un zombie");
    sprintf(spid, "ps -o ppid,pid,state,command");
    system(spid);
    
//    wait(0); // Manière 2 d'éviter un zombie
    
    sprintf(spid, "ps -o ppid,pid,state,command");
    system(spid);
    exit (0);
}
