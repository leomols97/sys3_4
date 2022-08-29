/*
ipc029 : Écrivez 3 process.
Synchronisez ces process de telle façon que le process 3 ne peut s’exécuter que
quand les process 1 et 2 sont terminés.
L’ordre de lancement des process est quelconque.
Prouvez que votre synchronisation est correcte.
Vous devez utiliser les sémaphores SystemV pour résoudre cet exercice.
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
    op[0].sem_num = 0;
    op[0].sem_op = i;
    op[0].sem_flg = SEM_UNDO;
    if((n=semop(sem,op,1))==-1)
    {
        perror("semop");
        exit(1);
    }
    return(n);
}
int creeSem()
{
    return semget(IPC_PRIVATE,1,0666|IPC_CREAT);
}
void initsem(int sem, int val)
{
    if(semctl(sem,0,SETVAL,val)==-1) // une ressource pour une SC
        perror("semctl");//idk
}
void supsem(int sem)
{
    if(semctl(sem,0,IPC_RMID)!=0)
        perror("semctl");
}
void down(int sem)
{
    opsem(sem, -1);
}
void up(int sem)
{
    opsem(sem, +1);
}
void zero(int sem)
{
    while(sem != 0)
        pause();
}

int sem, semUn, semDeux;
char un = 0;
char deux = 0;

void creatChild(int nb)
{
    if(fork() == 0)
    {
        if(nb == 3)
        { //si on est process 3, on fait un down sem1 et 1 down sem2
            down(semUn);
            down(semDeux);
        }
        down(sem);
        
        //début de la section critique
        if(nb == 1)
            up(semUn);
        if(nb == 2)
            up(semDeux);
        printf("%d\n", nb);
        //fin de la section critique

        up(sem);

        sleep(1);
        exit(0);
    }
}

int main(int argc, char *argv[]){
    sem = creeSem();
    initsem(sem, 1); //1 car 1 seul a la fois dans la SC

    semUn = creeSem();
    initsem(semUn, 0); //0 donc directement bloqué tant que y a pas de up(ligne 78)

    semDeux = creeSem();
    initsem(semUn, 0); //bloqué, attends le up de la ligne 80

    int nbProcess = 3;

    for(int i = nbProcess; i > 0; i--) // affiche 2 1 3 // for(int i = 1; i <= nbProcess; i++) // si on met ca affichera 1 2 3
        creatChild(i);
    
    for(int i = 0; i < nbProcess; i++)
        wait(0); //attends que les fils soient finis pour supprimer les semaphores

    supsem(sem);
    supsem(semUn);
    supsem(semDeux);
    exit(0);
}

// gcc ipc029.c lib.c -std=c99 -pedantic-errors -Iinclude -Wall -o ipc029 && ./ipc029

//affiche 2 1
