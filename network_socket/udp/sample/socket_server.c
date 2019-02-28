/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 17-feb-2019           */
/* Filename	: socket_server.c       */
/* Description	: socket sample program */
/****************************************/

/* Included header file */
#include "socket_server.h"

/* Global variable definitions */


/* function definitions */

int main()
{
	int socket_fd1;

	socklen_t length;

	char str1[200];

	struct sockaddr_un unix_addr;

	unix_addr.sun_family = AF_UNIX;

	strcpy(unix_addr.sun_path,"./socket1");


	//opening a new socket, with DGRAM type protocol
	socket_fd1 = socket(AF_UNIX,SOCK_DGRAM,0);
	perror("socket");

	//binding with 'socket1' socket file
	bind(socket_fd1,(struct sockaddr *)&unix_addr,sizeof(unix_addr));


	//sending first message
	recvfrom(socket_fd1,str1,100,0,(struct sockaddr *)&unix_addr,&length);
	perror("recvfrom");

	printf("%s\n",str1);

	close(socket_fd1);
}
