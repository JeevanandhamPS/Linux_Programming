/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 17-feb-2019           */
/* Filename	: socket_client.c       */
/* Description	: socket sample program */
/****************************************/

/* Included header file */
#include "socket_client.h"

/* Global variable definitions */


/* function definitions */

int main()
{
	char str1[] = "Message from client\n";
	
	int socket_fd1;

	struct sockaddr_un unix_addr;

	unix_addr.sun_family = AF_UNIX;

	strcpy(unix_addr.sun_path,"./socket1");

	//opening a new socket, with DGRAM type protocol
	socket_fd1 = socket(AF_UNIX,SOCK_DGRAM,0);
	perror("socket");

	//sending first message
	sendto(socket_fd1,str1,strlen(str1)+1,0,(struct sockaddr *)&unix_addr,sizeof(unix_addr));
	perror("sendto");

	sleep(2);

	close(socket_fd1);
}
