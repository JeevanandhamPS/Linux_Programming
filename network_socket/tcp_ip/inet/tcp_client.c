/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 27-feb-2019           */
/* Filename	: tcp_client.c          */
/* Description	: tcp/ip INET program   */
/****************************************/

/* Included header file */

#include "tcp_client.h"

/* Global variable definitions */

/* function definitions */
 
int main(int argc, char *argv[])
{
	int socket_fd, sock_fd_new, backlog = 10;

	ssize_t write_t;

	struct sockaddr_in socketaddr;

	socklen_t length = sizeof(socketaddr);
	
	/* Create a new socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd == -1)
		perror("socket");

	/* Upload the values to the structure */
	socketaddr.sin_family = AF_INET; /* family always AF_INET for internet protocol*/
	socketaddr.sin_port   = htons(atoi(argv[1])); /* assign the port number */
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr); /* store the ip address as network byte oreder */

	/* Connect with server via connect sys call */
	if(connect(socket_fd,(struct sockaddr *)&socketaddr,sizeof(struct sockaddr_un)) == -1)
		perror("connect");
	
	/* Write a content to socket */
	write_t = write(socket_fd,"Client in online",20);

	if(write_t == -1)
		perror("write");
}
