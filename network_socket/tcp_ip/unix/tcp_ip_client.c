/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 27-feb-2019           */
/* Filename	: tcp_ip_client.c       */
/* Description	: tcp_ip sample program */
/****************************************/

/* Included header file */

#include "tcp_ip_client.h"

/* Global variable definitions */


/* function definitions */
 
int main()
{
	int socket_fd, sock_fd_new, backlog = 10;

	unsigned char msg[] = "TCP/IP client as connected" ;

	ssize_t write_t;

	struct sockaddr_un socketaddr;

	socklen_t length = sizeof(socketaddr);

	/* Upload the values to the structure */
	socketaddr.sun_family = AF_UNIX; /* family always AF_UNIX for unix socket */
	strcpy(socketaddr.sun_path,"./tcp_ip_socket"); /* path for the socket */

	/* Create a socket */
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0); /* SOCK_STRAEM for stream socket*/

	/* if socket not created, print the error message */
	if(socket_fd == -1)
		perror("socket");

	/* connect with the server end via connect sys call() */
	if(connect(socket_fd,(struct sockaddr *)&socketaddr,sizeof(struct sockaddr_un)) == -1)
		perror("connect");

	/* Write the message to the socket */
	write_t = write(socket_fd,msg,100);

	if(write_t == -1)
		perror("write");
}
