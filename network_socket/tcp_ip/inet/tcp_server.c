/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 27-feb-2019           */
/* Filename	: tcp_server.c          */
/* Description	: tcp/ip INET program  */
/****************************************/

/* Included header file */

#include "tcp_server.h"

/* Global variable definitions */


/* function definitions */
 
int main(int argc, char *argv[])
{
	int socket_fd, sock_fd_new, backlog = 10;

	unsigned char msg[100];

	ssize_t read_t;

	struct sockaddr_in socketaddr;

	socklen_t length = sizeof(socketaddr);

	/* map the size to the structure */
	memset(&socketaddr, 0, sizeof(struct sockaddr_in));

	/* Create a new socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM for stream socket

	/* print the error message */
	if(socket_fd == -1)
		perror("socket");

	/* Upload the values to the structure */
	socketaddr.sin_family = AF_INET;	/* family always AF_INET for internet protocol*/

	socketaddr.sin_port   = htons(atoi(argv[1])); /* assign port number */

	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr); /* store ip address as network byte order */

	/* Bind the socket with local address */
	if(bind(socket_fd,(struct sockaddr *)&socketaddr,length) == -1) 
		perror("bind");

	/* Listen for the client */
	if(listen(socket_fd,backlog) == -1)
		perror("listen");


	/* After listening accept the client */
	sock_fd_new = accept(socket_fd, NULL, NULL);

	if(sock_fd_new == -1)
		perror("accept");

	/* read the msg from socket */
	read_t = read(sock_fd_new,msg,100);

	if(read_t == -1)
		perror("read");

	/* print the receive message */
	printf("%s\n",msg);		

	close(sock_fd_new);
}
