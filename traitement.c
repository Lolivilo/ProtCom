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


int traiterPaquet(paquet *paq, int enviParler, char myip[LONGUEUR_ADRESSE])
{
    if( (strcmp(paq->ipDest,myip) != 0) && (paq->flag == 1))
    {
        return 0;
    }
    else
    {
        if(paq->flag == 1)
        {
            effacerPaquet(paq);
        }
        else
        {
        		printf("get data ->\n");
            GetData(paq); // Récupération des données
            printf("remplir ->\n");
            RemplirPaquet(paq->ipSrc,myip, "", 1, paq); // Envoi de l'accusé de reception
            printf("fin else ->\n");
            return 0;
        }
    }
    if(enviParler)
    {
        effacerPaquet(paq);
        char ipDest[LONGUEUR_ADRESSE];
        char data[LONGUEUR_MESSAGE];
        
        DemanderDataPaquet(ipDest, data);
        RemplirPaquet(ipDest, myip, data, 0, paq);
        
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
    printf("DATA : %s", paq->data);
}

void RemplirPaquet(char dest[LONGUEUR_ADRESSE], char src[LONGUEUR_ADRESSE], char data[LONGUEUR_MESSAGE], int flag, paquet *paq)
{
    strcpy(paq->ipSrc, dest);
    strcpy(paq->ipDest, src);
    strcpy(paq->data, data);
    paq->flag = flag;
    
}
