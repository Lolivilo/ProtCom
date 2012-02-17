//
//  ihm.c
//  Tp1_reseau
//
//  Created by Antonin Biret on 15/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "paquet.h"

void DemanderDataPaquet(char ipDest[LONGUEUR_ADRESSE], char data[LONGUEUR_MESSAGE])
{
    printf("Destinataire :\t");
    scanf("%s",ipDest);
    printf("\nData :\t");
    scanf("%s",data);
}