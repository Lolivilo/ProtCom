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
    if( (strcmp(paq->ipDest,myip) != 0)/* && (paq->flag == 1)*/) // Paquet n'est pas pour nous
    {
        return 0;
    }
    else
    {
        if(paq->flag == 1)
        {
            effacerPaquet(paq);
            printf("ACCUSE DE RECEPTION RECU\n");
        }
        else
        {
            GetData(paq); // Récupération des données
            RemplirPaquet(paq->ipSrc,myip, "", 1, paq); // Envoi de l'accusé de reception
            return 0;
        }
    }
    if(parle->envie == 1)
    {
        effacerPaquet(paq);
        RemplirPaquet(parle->ipDest, myip, parle->data, 0, paq);
        parle->envie = 0;
        
    }
    return 0;
}

void effacerPaquet(paquet *paq)
{
    for(int i=0;i<LONGUEUR_ADRESSE;i++)
        paq->ipDest[i] = '0';
    for(int i=0;i<LONGUEUR_ADRESSE;i++)
        paq->ipSrc[i] = '0';
    for(int i=0;i<LONGUEUR_MESSAGE;i++)
        paq->data[i] = ' ';
    
    paq->flag = 0;  
}

void GetData(paquet *paq)
{
    printf("PAQUET RECU NOUS ETANT DESTINE; IP DE LA DESTINATION:%s\tDONNEES:%s\n", paq-> ipSrc,paq->data);
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
    char *temp = malloc(strlen(buffer)*sizeof(char));
    temp = strcpy(temp,buffer);
    strcpy(p->ipDest,strtok(temp, limiter));
    strcpy(p->ipSrc,strtok(NULL, limiter));
    char flagChar[1];
    strcpy(flagChar,strtok(NULL, limiter));
    p->flag = atoi(flagChar);
    strcpy(p->data,strtok(NULL, limiter));
}
