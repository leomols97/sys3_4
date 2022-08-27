/*
NOM    	: Create2BlocksSizeFile.c
CLASSE 	: FilesCreation
AUTEUR	: Léopold Mols
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main ( int argc, char * argv[] )
{
	int fd;
	char bufA[] = "123456";
	char bufB[] = "7890";
	fd = open("2blocks.txt", O_CREAT | O_WRONLY, 0666);
	if (fd < 0)
	{
		perror("Fichier non créé");
		exit(1);
	}
	write(fd, bufA, strlen(bufA));
	lseek(fd, 3000, SEEK_SET);
	write(fd, bufB, strlen(bufB));
	close(fd);
  	exit(0);
}
