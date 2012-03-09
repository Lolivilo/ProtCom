//
//  traitement.c
//  Tp1_reseau
//
//  Created by Antonin Biret on 15/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "paquet.h"
#include "traitement.h"
#include "ihm.h"
#include <stdlib.h>


int traiterPaquet(paquet *paq, parler *parle, char myip[LONGUEUR_ADRESSE])
{
    if( (strcmp(paq->ipDest,myip) != 0) && !paqIsEmpty(paq)) // Paquet n'est pas pour nous et qu'il est non vide (il est destiné à quelqu'un) donc on le fait suivre
    {
        return 0;
    }
    else if((strcmp(paq->ipDest,myip) == 0))// paquet pour nous
    {
        if(paq->flag == 1) // c'est un paquet accusé de reception
        {
            printf("ACCUSE DE RECEPTION RECU\n");
            effacerPaquet(paq);
           // printf("PAQUET VIDE CREE : 
            
        }
        else // c'est un paquet de données
        {
            GetData(paq); // Récupération des données
            char SourcePaq[LONGUEUR_ADRESSE];
            char DestPaq[LONGUEUR_ADRESSE];
            strcpy(SourcePaq,paq->ipDest);
            strcpy(DestPaq,paq->ipSrc);
            effacerPaquet(paq);
            RemplirPaquet(DestPaq,SourcePaq, "ACCUSE", 1, paq); // Envoi de l'accusé de reception
            printf("PAQUET ACCUSE RECEPTION CREE : IP DESTINATION:%s\t;IP SRC:%s\tFLAG:%d\tDATA:%s\n",paq->ipDest, paq->ipSrc, paq->flag, paq->data);
            return 0;
        }
    }
    if(parle->envie == 1) //ici le paquet est libre, donc on peut parler si on veut
    {
        effacerPaquet(paq);
        RemplirPaquet(parle->ipDest, myip, parle->data, 0, paq);
        parle->envie = 0;
        
    }
    return 0;
}

void effacerPaquet(paquet *paq)
{
    strcpy(paq->ipDest, "0");
    strcpy(paq->ipSrc, "0");
    strcpy(paq->data, "VIDE");
    
    paq->flag = 2;  
}

void GetData(paquet *paq)
{
    printf("PAQUET RECU NOUS ETANT DESTINE; IP DE LA DESTINATION PAQUET:%s SRC:%s Flag:%d\tDONNEES:%s\n", paq->ipDest,paq->ipSrc, paq->flag,paq->data);
}

void RemplirPaquet(char dest[LONGUEUR_ADRESSE], char src[LONGUEUR_ADRESSE], char data[LONGUEUR_MESSAGE], int flag, paquet *paq)
{
    strcpy(paq->ipSrc, src);
    strcpy(paq->ipDest, dest);
    strcpy(paq->data, data);
    paq->flag = flag;
    
}

void bufferToPaquet(char * buffer, paquet *p, const char *limiter )
{
    //printf("BUF\t%s\n",buffer);
    char *temp = malloc(strlen(buffer)*sizeof(char));
    temp = strcpy(temp,buffer);
    strcpy(p->ipDest,strtok(temp, limiter));
    strcpy(p->ipSrc,strtok(NULL, limiter));
    char flagChar[1];
    strcpy(flagChar,strtok(NULL, limiter));
    p->flag = atoi(flagChar);
    strcpy(p->data,strtok(NULL, limiter));
    //printf("FIN BUF\n");
}

int paqIsEmpty(paquet *p)
{
	if(p->flag == 2)
		return 1;
	return 0;
} 
