/*
NOM    	: AttachShm.c
CLASSE 	: IPC - LaboIPC 01-01
#OBJET  : réservé au makefile
AUTEUR	: J.C. Jaumain, 07/2011
	: MBA 11/2017
 	: NVS 2021
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
    int shm1,shm2;
	char * c;
	int * i;
	
    shm1 = shmget(256,1,0777/*|IPC_CREAT*/);
	shm2 = shmget(512,4,0777/*|IPC_CREAT*/);
	
    if (shm1 >= 0 && shm2 >= 0)
	{
		c=shmat(shm1,0,0777);
		i=shmat(shm2,0,0777);
		printf ("shm1=%d, c=%c, shm2=%d, i=%d\n", shm1, *c, shm2, *i);
		shmdt(c);
		shmdt(i);
	}
	else
	{
		printf("Erreur de shmat %d %d\n", shm1, shm2);
	}
	exit(0); 
}
		
