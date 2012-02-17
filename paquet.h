//
//  paquet.h
//  Tp1_reseau
//
//  Created by Antonin Biret on 15/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tp1_reseau_paquet_h
	#define Tp1_reseau_paquet_h
	#define LONGUEUR_MESSAGE 30
	#define LONGUEUR_ADRESSE 16

typedef struct paquet
{
    char ipDest[LONGUEUR_ADRESSE];
    char ipSrc[LONGUEUR_ADRESSE];
    int flag;
    char data[LONGUEUR_MESSAGE];
} paquet;


#endif
