/**
 Créer un programme qui crée 2 process : l'un affiche 'Bonjour, ', l'autre 'il fait beau\n', chacun à leur tour
 
 Résultat à avoir (peut avoir plus ou moins de ligne que cela, mais minimum une, je pense) :
 Bonjour, il fait beau
 Bonjour, il fait beau
 Bonjour, il fait beau
 ...
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
    
//    if ((n=semop(sem,op,1))==-1)
//    {    perror ("semop");
//        exit(1);
//    }
    return(n);
}

int main(int argc, char * argv[])
{
    int n,sem,s;
    char errorMsg[100];
    
    if (s==1)
    {
        if (sem=semget(IPC_PRIVATE,1,0666|IPC_CREAT) == -1)
        {
            perror ("semget");
            exit(-1);
        }

        // SETVAL : Mettre un des sémaphores à la valeur spécifiée : le dernier argument, soit à 1
//        if (semctl(sem,0,SETVAL,1) == -1) // une ressource pour une SC
//        {
//            perror ("semctl");
//            exit(1);
//        }
    }
    
    while(1)
    {
        if(fork() == 0)
        {
            if (s==1)
                opsem(sem, -1); // down
            execlp("echo", "echo", "Bonjour, ", 0);
            sprintf(errorMsg, "execlp didn't went well\n");
            perror(errorMsg);
        }
        if (s==1)
            opsem(sem, +1); // up
        wait(0);

        if(fork() == 0)
        {
            if (s==1)
                opsem(sem, -1); // down
            execlp("echo", "echo", "il fait beau\n", 0);
            sprintf(errorMsg, "execlp didn't went well\n");
            perror(errorMsg);
        }
        if (s==1)
            opsem(sem, +1); // up
        wait(0);
    }
    exit(0);
}
