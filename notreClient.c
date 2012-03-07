#include <stdlib.h>
#include <stdio.h>
#include "paquet.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "traitement.h"
#include <string.h>
#include "notreClient.h"




int recevoirPaquet(int sock_Rec, paquet* p, struct sockaddr* sa_Rec ,unsigned int *taille_sa)
{
	char buffer[2*LONGUEUR_ADRESSE + sizeof(int) + LONGUEUR_MESSAGE + 3*sizeof(char)];
	int sizebuff = 2*LONGUEUR_ADRESSE + sizeof(int) + LONGUEUR_MESSAGE + 3*sizeof(char);
	memset (buffer, '\0', sizebuff*sizeof(char));

	if ((recvfrom(sock_Rec, buffer, sizebuff*sizeof(char), 0, (struct sockaddr *) sa_Rec, taille_sa)) == -1)
	{
		perror("Receive");
		printf("Erreur lors de la lecture ! \n");
		return 0;
	}
	//sscanf(buffer, "%s|%s|%d|%s", (char*)&(p->ipDest), (char*)&(p->ipSrc), &(p->flag), (char*)&(p->data));
    bufferToPaquet(buffer, p, "|" );

	return 1;
}

int envoyerPaquet(int sock_Env, paquet* p, struct sockaddr* sa_Env ,unsigned int taille_sa)
{
	char buffer[2*LONGUEUR_ADRESSE + sizeof(int) + LONGUEUR_MESSAGE + 3*sizeof(char)];
	int sizebuff = 2*LONGUEUR_ADRESSE + sizeof(int) + LONGUEUR_MESSAGE + 3*sizeof(char);
	sprintf(buffer, "%s|%s|%d|%s", p->ipDest, p->ipSrc, p->flag, p->data);

	if ((sendto(sock_Env, buffer, sizebuff*sizeof(char), 0, (struct sockaddr*) sa_Env, taille_sa)) != sizebuff)
	{
		printf("Erreur lors de l'écriture ! \n");
		return 0;
	}

  	return 1;
}





