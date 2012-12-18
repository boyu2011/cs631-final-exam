/*
	send.c

    Write a simple program that opens a TCP connection to the IP address
    2001:470:1f06:1a3::2 on port 3113 and sends it the string given as
    the first argument of the command.  Make sure to include all error
    checking as usual.

    $ ./send hello
    $

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET_IP_ADDR "2001:470:1f06:1a3::2"
#define TARGET_PORT 3113

int main ( int argc, char ** argv )
{
	int socket_fd;
	struct sockaddr_in6 target_addr;

	if ( argc != 2 )
	{
		printf ( "Usage: send message\n" );
		exit(1);
	}

	/* Create socket */
	socket_fd = socket ( AF_INET6, SOCK_STREAM, 0 );
	if ( socket_fd < 0 )
	{
		perror ( "opening stream socket" );
		exit(1);
	}

	/* Convert presentation format address to network format */
	if ( inet_pton ( AF_INET6, TARGET_IP_ADDR, 
					 target_addr.sin6_addr.s6_addr ) != 1 )
	{
		perror ( "inet_pton()" );
		exit(1);
	}

	target_addr.sin6_family = AF_INET6;
	target_addr.sin6_port = htons ( TARGET_PORT );

	/* To create a connection */
	if ( connect ( socket_fd, (struct sockaddr *)&target_addr, 
				   sizeof(target_addr) ) < 0 )
	{
		perror ( "connecting stream socket" );
		exit(1);
	}

	/* Send message */
	if ( write ( socket_fd, argv[1], strlen(argv[1]) ) != strlen(argv[1]) )
	{
		perror ( "writing on stream socket" );
		exit(1);
	}

	/* Close socket */
	if ( close ( socket_fd ) == -1 )
	{
		perror ( "close()" );
		exit(1);
	}

	exit(0);
}
