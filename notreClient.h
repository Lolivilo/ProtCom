#ifndef NOTRECLIENT_H
	#define NOTRECLIENT_H

#include "paquet.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int recevoirPaquet(int sock_C, paquet* p, struct sockaddr* sa_S ,unsigned int taille_sa_S);

int envoyerPaquet(int sock_C, paquet* p, struct sockaddr* sa_S ,unsigned int taille_sa_S);

#endif
