#include <stdio.h>	// perror
#include <netdb.h>	// socket, connect, hostent
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>
#include <string.h>

int creePriseEmission (char *server, int port)
{
    

    return sock;
}

int creePriseReception (int port)
{
    int			sock;
    struct sockaddr_in	address;
    if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) == -1)
    {
			perror ("creerPriseReception");
    		exit (1);
    }
    memset (&address, 0, sizeof (address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons (port);
    if (bind (sock,(struct sockaddr*) &address,sizeof (address)) == -1)
    {
			perror ("creerPriseReception");
			exit (1);
    }
    return sock;
}
