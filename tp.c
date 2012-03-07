#include <stdio.h>
#include <stdlib.h>
#include "notreClient.h"
#include "paquet.h"
#include "traitement.h"
#include <strings.h>
#include <string.h>
#include "ihm.h"


int main(int argc, const char* argv[])
{
    hote local, suivant; // adresse et port des machines
    parler parle; // contients les données à envoyer et si un message est prets à etre envoyé
    parle.envie = 0;
    paquet p;
    if(argc < 3)
    {
        printf("Il faut minimum 2 arguments :\texe ipLocale:Port ipSuivante:Port ");
        exit(-1);
    }
    
    ConvertArgToIpAndPort((char *)argv[1],&local);
    ConvertArgToIpAndPort((char *)argv[2],&suivant);

    printf("Local:\tIP : '%s'\tPORT:'%d'\n",local.ip,local.port);
    printf("Suivant:IP : '%s'\tPORT:'%d'\n",suivant.ip,suivant.port);
	/*RESEAU*/
	struct sockaddr_in sa_Loc, sa_Suiv;
	unsigned int taille_sa;
	
	int sock_Loc, sock_Suiv;
	/* creation socket Client */
	sock_Loc = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_Loc == -1)
        perror("socket");
	sock_Suiv = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock_Suiv == -1)
        perror("socket");
	
	
	/* @IP et n° port En ecoute */
	bzero((char*) &sa_Loc, sizeof(sa_Loc));
	sa_Loc.sin_family      = AF_INET;
	sa_Loc.sin_addr.s_addr = inet_addr( local.ip );
	sa_Loc.sin_port        = htons( local.port );
	
	/* @IP et n° port En envoi */
	bzero((char*) &sa_Suiv, sizeof(sa_Suiv));
	sa_Suiv.sin_family      = AF_INET;
	sa_Suiv.sin_addr.s_addr = inet_addr( suivant.ip );
	sa_Suiv.sin_port        = htons( suivant.port );
	
	/* emission vers le serveur (a partir du client) */
	taille_sa = sizeof( struct sockaddr );
	if(bind(sock_Loc, (struct sockaddr *) &sa_Loc, sizeof(struct sockaddr)) == -1 )
        perror("bind_Ecoute ");
	

	

	if (argc > 3 && (strcmp(argv[3], "INIT") == 0) )	//l'hote envoie le premier message (vide)
	{
        printf("Envoi du paquet INIT...\n");
		effacerPaquet(&p);
		strcpy(p.ipDest, suivant.ip );
		strcpy(p.ipSrc, local.ip );
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
		if (!(recevoirPaquet(sock_Loc, &p, (struct sockaddr*) &sa_Loc, &taille_sa))) // attention si ca plante, réinitialiser la taille_sa
		{
			printf("Erreur lors de la reception \n");
			exit(0);
		}
        printf("UN PAQUET A ETE RECU\n");

		DemanderDataPaquet(&parle);
        if(parle.envie == 1)
        {
            RemplirPaquet(parle.ipDest, local.ip, parle.data, 0, &p);
            printf("NOUVEAU PAQUET CREE : IPD:%s IPS:%s DATA:%s FLAG:%d\n",p.ipDest,p.ipSrc,p.data,p.flag);
        }

		traiterPaquet(&p, &parle, local.ip);

		if (!(envoyerPaquet(sock_Suiv, &p, (struct sockaddr*) &sa_Suiv, taille_sa)))
		{
			printf("Erreur lors de l'envoi \n");
			exit(0);
		}
        printf("UN PAQUET A ETE ENVOYE\n");

	}

	return 0;
}
