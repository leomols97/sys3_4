#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int opsem ( int sem , int i)
{
    int n;
    struct sembuf op [1];
    op [0].sem_num = 0; // premier et unique sé maphore
    op [0].sem_op = i ;
    op [0].sem_flg = 0;
    if ((n= semop (sem,op,1))== -1)
    {
        perror (" semop " );
        exit (1);
    }
    return(n);
}

int main ( int argc , char * argv [])
{
    int sem = semget(123,1,IPC_CREAT|0666);
    semctl(sem,0,SETVAL,1);
    while(1)
    {
        opsem(sem,-1);
        printf("2");
        opsem(sem,1);
    }
}
