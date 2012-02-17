/* Socket - Serveur - Mode Datagramme */

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>

#define UDP_port_S 8000

int main()
{
	int sock_S;
	
	char message[10];
	struct sockaddr_in sa_S, sa_C;

	unsigned int taille_sa_C;
	
	/* creation socket Serveur*/
	sock_S = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket ");
	
	/* @IP et n° port Serveur */
	bzero((char*) &sa_S, sizeof(sa_S));
	sa_S.sin_family      = AF_INET;
	sa_S.sin_addr.s_addr = htonl( INADDR_ANY );
	sa_S.sin_port        = htons( UDP_port_S );

	/* Attachement */
	bind(sock_S, (struct sockaddr *) &sa_S, sizeof(struct sockaddr));
	perror("bind ");

	/* reception datagramme */
	taille_sa_C = sizeof( struct sockaddr );
	
	while(1)
	{
		/* reception datagramme du client*/
		recvfrom(sock_S, message, 10 * sizeof(char), 0, (struct sockaddr *) &sa_C, &taille_sa_C);
		
		/* affichage */
		printf("%s \n", message);
		
		/* re-emission datagramme vers client */
		sendto(sock_S, "re-salut", 10 * sizeof(char), 0, (struct sockaddr*) &sa_C, taille_sa_C);
	}

	/* fin */

	exit(EXIT_SUCCESS);
	
}
