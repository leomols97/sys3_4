/*
NOM    	: Critique.c
CLASSE 	: IPC - LaboIPC 02-01
#OBJET  : réservé au makefile
AUTEUR	: J.C. Jaumain, 07/2011
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int opsem(int sem, int i)
{
    int n;
    struct sembuf op[1];
	
    op[0].sem_num = 0; // premier et unique sémaphore
	op[0].sem_op = i;
	op[0].sem_flg = SEM_UNDO; //
	
    if ((n=semop(sem,op,1))==-1)
	{	perror ("semop");
		exit(1);
	}
	return(n);
}

int main (int argc, char * argv[])
{
    int n,sem,s;
	char buff[100];
	
    if ((argc==2) && (strcmp(argv[1],"ns")==0))
        s=0;
    else
        s=1;
	
    if (s==1)
    {
	        if (sem=semget(IPC_PRIVATE,1,0666|IPC_CREAT) == -1)
	        {
                perror ("semget");
	        	exit(-1);
	        }

            // SETVAL : Mettre un des sémaphores à la valeur spécifiée : le dernier argument, soit à 1
 	        if (semctl(sem,0,SETVAL,1) == -1) // une ressource pour une SC
	        {
                perror ("semctl");
		        exit(1);
	        }
	}
    
	if (fork()==0)
	{
        do
		{
            if (s==1)
                opsem(sem, -1); // down
            
			printf("[fils] : Je veux lire\n");
			n=read(0,buff,100);
			printf("Le fils a lu : [%s]\n",buff);
            
			if (s==1)
                opsem(sem, +1); // up
			buff[n-1]=0;
		} while (strcmp(buff,"quit")!=0);
		printf("Le fils a terminé \n");
		exit(0); 
	}
	
    do
	{
        if (s==1)
            opsem(sem, -1); // down
		
        printf("[père] : Je veux lire\n");
		n=read(0,buff,100);
		printf("Le père a lu : [%s]\n",buff);
		
        if (s==1)
            opsem(sem, +1); // up
		
        buff[n-1]=0;
	} while (strcmp(buff,"quit")!=0);
    printf("Le père a terminé \n");
	wait(0);
	
    if (s==1)
 	        if (semctl(sem,0,IPC_RMID)!=0)
	        {
                perror ("semctl");
		        exit(1);
	        }
	exit(0); 
}
