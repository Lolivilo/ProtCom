#include <stdio.h>
#include <stdlib.h>
#include "notreClient.h"
#include "paquet.h"
#include "prise.h"
#include "traitement.h"
#include <strings.h>


#define PORT 8000
#define ADRESSE_SUIVANT "127.0.0.1"
#define ADRESSE_HOTE "127.0.0.1"

int main(int argc, const char* argv[])
{

	
	/*RESEAU*/
	struct sockaddr_in sa_S;
	unsigned int taille_sa_S;
	int sock_C;
	/* creation socket Client */
	sock_C = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket");
	/* @IP et n° port Serveur */
	bzero((char*) &sa_S, sizeof(sa_S));
	sa_S.sin_family      = AF_INET;
	sa_S.sin_addr.s_addr = inet_addr( ADRESSE_HOTE );
	sa_S.sin_port        = htons( PORT );
	/* emission vers le serveur (a partir du client) */
	taille_sa_S = sizeof( struct sockaddr );

	bind(sock_C, (struct sockaddr *) &sa_S, sizeof(struct sockaddr));
	perror("bind ");

	int envieParler;
	paquet p;

	if (argc == 2)	//l'hote envoie le premier message (vide)
	{
		effacerPaquet(&p);
		if (!(envoyerPaquet(sock_C, &p, (struct sockaddr*) &sa_S, taille_sa_S)))
		{
			printf("Erreur lors de l'envoi \n");
			exit(0);
		}
	}
	
	while(1)
	{
		envieParler = 0;
		if (!(recevoirPaquet(sock_C, &p, (struct sockaddr*) &sa_S, taille_sa_S)))
		{
			printf("Erreur lors de la reception \n");
			exit(0);
		}

		if (getchar() == 'e')
			envieParler = 1;

		traiterPaquet(&p, envieParler, ADRESSE_HOTE);

		if (!(envoyerPaquet(sock_C, &p, (struct sockaddr*) &sa_S, taille_sa_S)))
		{
			printf("Erreur lors de l'envoi \n");
			exit(0);
		}

	}

	return 0;
}
