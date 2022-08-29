/**
 Ipc032 : Un process crée une réserve de N cacahouètes. N est un nombre compris entre 1000 et 2000. 3 processus fils sont des mangeurs de cacahouètes (M à la fois). M est un nombre aléatoire compris entre 100 et 200. Les processus fils affichent sur 3 lignes "je suis le processus <pid> , je vole M cacahuètes, je pars". Les fils meurent quand il ne reste plus suffisament de cacahouètes dans la réserve. Le parent meurt quand les 3 fils sont morts. Les messages ne peuvent pas être mélangés et le nombre de cachuètes disponibles respecté. Vous ne pouvez pas utiliser de mémoire partagée dans cet exercice.
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

int randomBetween(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main(int argc, char * argv[])
{
    int nbCacahuetes = randomBetween(1000,2000);
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
    
    int filsUnMange = randomBetween(100, 200);
    int pidFils1;
    int filsDeuxMange = randomBetween(100, 200);
    int pidFils2;
    int filsTroisMange = randomBetween(100, 200);
    int pidFils3;
    int pids[3];
    
    if(fork() == 0)
    {
        pidFils1 = getpid();
        pids[0] = getpid();
//        printf("Je suis le fils %d\n", getpid());
        if(fork() == 0)
        {
            pidFils2 = getpid();
            pids[1] = getpid();
//            printf("Je suis le fils %d\n", getpid());
            if(fork() == 0)
            {
                pidFils3 = getpid();
                pids[2] = getpid();
//                printf("Je suis le fils %d\n", getpid());
            }
            wait(0);
        }
        wait(0);
    }
    wait(0);
    
    while(nbCacahuetes - filsUnMange > 0
          && nbCacahuetes - filsDeuxMange > 0
          && nbCacahuetes - filsTroisMange > 0)
    {
        printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils1, filsUnMange, nbCacahuetes - filsUnMange);
        nbCacahuetes -= filsUnMange;
        printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils2, filsDeuxMange, nbCacahuetes - filsDeuxMange);
        nbCacahuetes -= filsDeuxMange;
        printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils3, filsTroisMange, nbCacahuetes - filsTroisMange);
        nbCacahuetes -= filsTroisMange;
        
//        if(pids[0] == pidFils1)
//        {
//            if (s==1)
//                opsem(sem, -1); // down
//            printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils1, filsUnMange, nbCacahuetes - filsUnMange);
//            exit(0);
//        }
//        nbCacahuetes -= filsUnMange;
//        if (s==1)
//            opsem(sem, +1); // up
////        wait(0);
//
//        if(pids[1] == pidFils2)
//        {
//            if (s==1)
//                opsem(sem, -1); // down
//            printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils2, filsDeuxMange, nbCacahuetes - filsDeuxMange);
//            exit(0);
//        }
//        nbCacahuetes -= filsDeuxMange;
//        if (s==1)
//            opsem(sem, +1); // up
////        wait(0);
//
//        if(pids[2] == pidFils3)
//        {
//            if (s==1)
//                opsem(sem, -1); // down
//            printf("Je suis le fils %d et mange %d cacahuetes. Il en reste %d\n", pidFils3, filsTroisMange, nbCacahuetes - filsTroisMange);
//            exit(0);
//        }
//        nbCacahuetes -= filsTroisMange;
//        if (s==1)
//            opsem(sem, +1); // up
////        wait(0);
    }
//    wait(0);
    exit(0);
}
