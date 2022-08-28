/*
NOM : gccAffMessage.c
CLASSE : Process - LaboProcess 02-02 #OBJET : réservé au Makefile
AUTEUR : J.C. Jaumain , 07/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
    int i;
    if(fork() == 0)
    {
        execlp("gcc", "gcc", "aff.c", "-o", "aff", 0);
        printf("Erreur : gcc non trouve\n");
        exit(0);
    }
    wait(&i);
    if (i != 0)
    {
        printf("Erreur de compilation du programme aff.c\n");
        exit(1);
    }
    execl("./aff","aff","Message",0);
    exit(0);
}
