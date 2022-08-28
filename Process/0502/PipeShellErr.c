#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main ()
{
    int fp1[2],fp2[2];
	char ligne[257];
	printf("Commande ?] ");
	fgets(ligne,256,stdin);
	while (strcmp(ligne,"exit\n"))
	{
        pipe(fp1);
        pipe(fp2);
		if (fork()==0)
		{
            dup2(fp1[1],1);
            close(fp1[0]);
            close(fp1[1]);
            close(fp2[0]);
            close(fp2[1]);
			execlp("cat","cat","/etc/passwd", 0);
		}
		if (fork()==0)
		{
            dup2(fp1[0],0);
			dup2(fp2[1],1);
            close(fp1[0]);
            close(fp1[1]);
            close(fp2[0]);
            close(fp2[1]);
			execlp("cut","cut","-f6", "PipeShellErr.c", 0);
		}
		if (fork()==0)
        {
            dup2(fp2[0],0);
            close(fp1[0]);
            close(fp1[1]);
            close(fp2[0]);
            close(fp2[1]);
			execlp("sort","sort", "-r", 0);
		}
		close(fp1[0]);
        close(fp1[1]);
        close(fp2[0]);
        close(fp2[1]);
		while(wait(0)>0);
		printf("Commande ?] ");
		fgets(ligne,256,stdin);
	}	
	exit(0);
}
