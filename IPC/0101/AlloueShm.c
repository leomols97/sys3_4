/*
 NOM    	: AlloueShm.c
 CLASSE 	: IPC - LaboIPC 01-01
 #OBJET  : réservé au makefile
 AUTEUR	: J.C. Jaumain, 07/2011
 : Ajout du while pause N. Vansteenkiste 2021
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>	// pour pause

int main(int argc, char * argv[])
{
    int shmid1,shmid2;
    char * c;
    int * i; // peut être de type 'char *'
    
    shmid1 = shmget(256,1,0777|IPC_CREAT);
    shmid2 = shmget(512,4,0777|IPC_CREAT);
    
    printf("shmid1=%d, shmid2=%d\n", shmid1,shmid2);
    
    c=shmat(shmid1,0,0777);
    i=shmat(shmid2,0,0777);
    *c='a';
    *i=1234; // car la taille de la mémoire partagée est de 4 byte, donc, il faut y stocker 4 caraactères
    
    // shmdt(c);
    //printf ("détachement explicite de shmid1=%d\n", shmid1);
    
    shmdt(i);
    printf ("détachement explicite de shmid2=%d\n", shmid2);
    
    while (1) pause();
    // boucle pour ne pas terminer Alloue
    // comme on ne s'est pas détaché de c, lorsque
    // FreeShm est exécuté, seule la variable partagée i
    // est détruite, pas celle associée à c
    // utiliser
    // $ ipcs -m
    // pour voir les mémoires partagées actives
    // quand on tue Alloue, il y a un détachement automatique
    // de c => à ce moment la zone mémoire liée à c est
    // détruite
    
    exit(0);
}

