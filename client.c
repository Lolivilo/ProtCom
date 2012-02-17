/* Socket - Client - Mode Datagramme */

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#define UDP_port_S 8000
#define IP_addr_S "127.0.0.1"

int main()
{
	int sock_C;
	
	struct sockaddr_in sa_S;
	
	unsigned int taille_sa_S;
	
	char message[10];
	
	/* creation socket Client */
	sock_C = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket");
	
	/* @IP et n° port Serveur */
	bzero((char*) &sa_S, sizeof(sa_S));
	sa_S.sin_family      = AF_INET;
	sa_S.sin_addr.s_addr = inet_addr( IP_addr_S );
	sa_S.sin_port        = htons( UDP_port_S );

	/* emission vers le serveur (a partir du client) */
	taille_sa_S = sizeof( struct sockaddr );
	
	sendto(sock_C, "Chevre", 10 * sizeof(char), 0, (struct sockaddr*) &sa_S, taille_sa_S);
	
	/* reception du serveur et affichage */
	recvfrom(sock_C, message, 10 * sizeof(char), 0, (struct sockaddr *) &sa_S, &taille_sa_S);
	
	printf("%s \n", message);
	
	/* fin */
	
	close( sock_C );
	exit(EXIT_SUCCESS);
	
}

