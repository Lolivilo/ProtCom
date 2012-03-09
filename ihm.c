//
//  ihm.c
//  Tp1_reseau
//
//  Created by Antonin Biret on 15/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "paquet.h"
#include <string.h>
#include <stdlib.h>

void DemanderDataPaquet(parler *parle)
{
    parle->envie = 0;
    if (getchar() == 'e')
        parle->envie = 1;
    
    if(parle->envie == 1)
    {
        printf("Destinataire :\t");
        scanf("%s",parle->ipDest);
        printf("\nData :\t");
        scanf("%s[^\ ]", parle->data);
        printf("\n");
    }
}

void ConvertArgToIpAndPort(char *arg, hote *hote)
{
    char *temp = malloc(strlen(arg)*sizeof(char));
    temp = strcpy(temp,arg);
    strcpy(hote->ip,strtok(temp, ":"));
    free(temp);
    char portString[4];
    strcpy(portString,strtok(NULL, ""));
    hote->port = atoi(portString);
}
