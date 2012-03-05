#include <stdio.h>
#include <stdlib.h>
#include "notreClient.h"
#include "paquet.h"
#include "traitement.h"
#include <strings.h>
#include <string.h>


#define PORT_LOC 8000
#define PORT_SUIV 8001
#define ADRESSE_SUIVANT "172.19.65.109"
#define ADRESSE_HOTE "172.19.65.101"

int main(int argc, const char* argv[])
{

	
	/*RESEAU*/
	struct sockaddr_in sa_Loc, sa_Suiv;
	unsigned int taille_sa;
	
	int sock_Loc, sock_Suiv;
	/* creation socket Client */
	sock_Loc = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket");
	sock_Suiv = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket");
	
	printf("Socket() Env : %d\n",sock_Suiv);
	printf("Socket() Rec: %d\n",sock_Loc);
	
	
	/* @IP et n° port En ecoute */
	bzero((char*) &sa_Loc, sizeof(sa_Loc));
	sa_Loc.sin_family      = AF_INET;
	sa_Loc.sin_addr.s_addr = inet_addr( ADRESSE_HOTE );
	sa_Loc.sin_port        = htons( PORT_LOC );
	
	/* @IP et n° port En envoi */
	bzero((char*) &sa_Suiv, sizeof(sa_Suiv));
	sa_Suiv.sin_family      = AF_INET;
	sa_Suiv.sin_addr.s_addr = inet_addr( ADRESSE_SUIVANT );
	sa_Suiv.sin_port        = htons( PORT_SUIV );
	
	/* emission vers le serveur (a partir du client) */
	taille_sa = sizeof( struct sockaddr );
	printf("Taille Sa : %d\n",taille_sa);
	bind(sock_Loc, (struct sockaddr *) &sa_Loc, sizeof(struct sockaddr));// Bind en écoute
	perror("bind_Ecoute ");
	

	int envieParler;
	paquet p;

	if (argc == 2)	//l'hote envoie le premier message (vide)
	{
		effacerPaquet(&p);
		strcpy(p.ipDest, ADRESSE_SUIVANT );
		strcpy(p.ipSrc, ADRESSE_HOTE );
		strcpy(p.data, "INIT" );
    	p.flag =0;
    	
		if (!(envoyerPaquet(sock_Suiv, &p, (struct sockaddr*) &sa_Suiv, taille_sa)))
		{
			printf("Erreur lors de l'envoi \n");
			exit(0);
		}
	}
	
	while(1)
	{
		envieParler = 0;
		if (!(recevoirPaquet(sock_Loc, &p, (struct sockaddr*) &sa_Loc, &taille_sa))) // attention si ca plante, réinitialiser la taille_sa
		{
			printf("Erreur lors de la reception \n");
			exit(0);
		}

		if (getchar() == 'e')
			envieParler = 1;

		traiterPaquet(&p, envieParler, ADRESSE_HOTE);

		if (!(envoyerPaquet(sock_Suiv, &p, (struct sockaddr*) &sa_Suiv, taille_sa)))
		{
			printf("Erreur lors de l'envoi \n");
			exit(0);
		}

	}

	return 0;
}
