/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 27-feb-2019           */
/* Filename	: tcp_ip_server.c       */
/* Description	: tcp_ip sample program */
/****************************************/

/* Included header file */

#include "tcp_ip_server.h"

/* Global variable definitions */


/* function definitions */
 
int main()
{
	int socket_fd, sock_fd_new, backlog = 10;

	unsigned char msg[100];

	ssize_t read_t;

	struct sockaddr_un socketaddr;

	socklen_t length = sizeof(socketaddr);

	/* Upload the values to the structure */ 
	 
	socketaddr.sun_family = AF_UNIX;  /* family is always AF_UNIX for unix socket */
	strcpy(socketaddr.sun_path,"./tcp_ip_socket"); /* path for the socket */

	/* Create a new socket */
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0); /* SOCK_STREAM  for Stream socket */

	/* if not create a socket, print the error */
	if(socket_fd == -1)
		perror("socket");

	/* Bind the socket with local address */
	if(bind(socket_fd,(struct sockaddr *)&socketaddr,length) == -1)
		perror("bind");
	
	/* listen for the client */
	if(listen(socket_fd,backlog) == -1)
		perror("listen");

	/* Accept the client */
	sock_fd_new = accept(socket_fd, NULL, NULL); /* sock_fd_new is new descriptor for access, the socket_fd always listen the new clients */

	if(sock_fd_new == -1)
		perror("accept");

	/* read the message from the socket */
	read_t = read(sock_fd_new,msg,100);

	if(read_t == -1)
		perror("read");

	/* print the received message */
	printf("%s\n",msg);		

	close(sock_fd_new); /* closed the sock_fd_new descriptor */

	close(socket_fd); /* closed the socet_fd descriptor*/
}
