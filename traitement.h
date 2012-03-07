//
//  traitement.h
//  Tp1_reseau
//
//  Created by Antonin Biret on 15/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tp1_reseau_traitement_h
#define Tp1_reseau_traitement_h

int traiterPaquet(paquet *paq, parler *parle, char myip[LONGUEUR_ADRESSE]);

void effacerPaquet(paquet *paq);

void GetData(paquet *paq);

void RemplirPaquet(char dest[LONGUEUR_ADRESSE], char src[LONGUEUR_ADRESSE], char data[LONGUEUR_MESSAGE], int flag, paquet *paq);

void bufferToPaquet(char * buffer, paquet *p, const char *limiter );
#endif
