/*
	listen.c

    Write a simple program that listens on the given UDP port on all IPv4
    interfaces of the host.  The program then reads any messages sent by
    any clients one line at a time and prints them prefixed with the
    client's hostname.

    $ ./listen 3113
    nemo.srcit.stevens-tech.edu hello
    avalon.srcit.stevens-tech.edu good day, everybody
    ^C
    $

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char ** argv )
{
	int socket_fd;
	int msg_socket;
	struct sockaddr_in server_ip;
	struct sockaddr_in client_ip_addr;
	socklen_t client_ip_addr_len = sizeof(client_ip_addr);
	char buf[1024];
	char hbuf[1024];	/* host name */

	if ( argc != 2 )
	{
		printf ( "Usage: listen port\n" );
		exit(1);
	}

	/* Create a socket */
	socket_fd = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( socket_fd < 0 )
	{
		perror ( "opening stream socket" );
		exit(1);
	}

	server_ip.sin_addr.s_addr = INADDR_ANY;
	server_ip.sin_family = AF_INET;
	server_ip.sin_port = htons ( atoi(argv[1]) );

	/* Binding the socket to an address */
	if ( bind ( socket_fd, (struct sockaddr *)&server_ip, sizeof(server_ip) ) )
	{
		perror ( "binding stream socket" );
		exit(1);
	}

	if ( listen ( socket_fd, 5 ) == -1 )
	{
		perror ( "listening stream socket" );
		exit(1);
	}

	/* Start accepting connection */
	while (1)
	{
		msg_socket = accept ( socket_fd, 
							  (struct sockaddr *)&client_ip_addr, 
							  &client_ip_addr_len );
		if ( msg_socket == -1 )
		{
			perror ( "accept()" );
		}

		memset ( buf, 0x0, sizeof(buf) );

		/* Get client hostname info */
		if ( getnameinfo ( (struct sockaddr * )&client_ip_addr,
						   client_ip_addr_len,
						   hbuf,
						   sizeof(hbuf),
						   NULL,
						   0,
						   NI_NAMEREQD ) )
		{
			perror ( "gethostinfo()" );
		}
		
		/* Read message from client */
		if ( read ( msg_socket, buf, sizeof(buf) ) < 0 )
		{
			perror ( "reading from client" );
		}
		/* Output message */
		else
		{
			printf ( "%s %s", hbuf, buf );
		}

		/* Close the connection */
		if ( close ( msg_socket ) == -1 )
		{
			perror ( "closing msg_socket" );
			exit(1);
		}
	}

	exit(0);
}

