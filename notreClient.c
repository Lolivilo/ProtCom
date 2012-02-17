#include <stdlib.h>
#include <stdio.h>
#include "paquet.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define UDP_port_S 8000


int recevoirPaquet(int sock_C, paquet* p, struct sockaddr* sa_S ,unsigned int taille_sa_S)
{
	char buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];

	memset (buffer, '\0', (LONGUEUR_ADRESSE + LONGUEUR_MESSAGE) * sizeof(char));
	if ((recvfrom(sock_C, buffer, strlen(buffer), 0, (struct sockaddr *) &sa_S, &taille_sa_S)) == -1)
	{
		printf("Erreur lors de la lecture ! \n");
		return 0;
	}
	sscanf(buffer, "%s|%s|%i|%s", (char*)&p->ipDest, (char*)&p->ipSrc, &p->flag, (char*)&p->data);

	return 1;
}

int envoyerPaquet(int sock_C, paquet* p, struct sockaddr* sa_S ,unsigned int taille_sa_S)
{
	char buffer[2*LONGUEUR_ADRESSE + sizeof(int) + LONGUEUR_MESSAGE + 3*sizeof(char)];

	sprintf(buffer, "%s|%s|%c|%s", p->ipDest, p->ipSrc, p->flag, p->data);
	if ((sendto(sock_C, buffer, strlen(buffer), 0, (struct sockaddr*) &sa_S, taille_sa_S)) != strlen(buffer))
	{
		printf("Erreur lors de l'écriture ! \n");
		return 0;
	}

  	return 1;
}



