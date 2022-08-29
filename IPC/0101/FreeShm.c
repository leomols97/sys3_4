/*
NOM    	: FreeShm.c
CLASSE 	: IPC - LaboIPC 01-01
#OBJET  : réservé au makefile
AUTEUR	: J.C. Jaumain, 07/2011
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char * argv[]) 
{
    int shmid;
    struct shmid_ds infos;
	int i;
	
    // test de tous les identifiants possibles
	//for (i=0;i<2147483647;i++)
	for (i=1;i<65536 ;i++) // 2147483647 est un peu long ...
	{
        if ((shmid = shmget(i,1,0777)) > 0 &&
		     shmctl(shmid,IPC_STAT,&infos)==0)
		{
            printf("\n\nClé identifiante : %5d\n",i);
			printf("Identifiant noyau : %5d\n",shmid);
			printf("Taille : %10d bytes\n",(int)infos.shm_segsz);
			printf("Process créateur : %d\n",infos.shm_cpid);
			printf("Process dernier accès : %d\n",infos.shm_lpid);
			printf("Nombre d'attachements : %d\n",(int)infos.shm_nattch);
			printf("Propriétaire de ce process : %d\n",infos.shm_perm.uid);
			printf("Date de dernier attachement : %s",ctime(&infos.shm_atime));
			printf("Du dernier détachement : %s",ctime(&infos.shm_dtime));
			printf("De la dernière modif droits : %s",ctime(&infos.shm_dtime));
			// marquage pour suppression
			if (shmctl(shmid,IPC_RMID,0) <0)
				perror ("semctl");
			else 
				printf("\nidentifiant %d marqué pour libération\n",shmid);
		}
	}
	exit(0);
}
