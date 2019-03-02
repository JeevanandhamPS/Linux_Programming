/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 27-feb-2019           */
/* Filename	: tcp_server.c          */
/* Description	: socket sample program */
/****************************************/

/* Included header file */

#include "tcp_server.h"

void *snd(); // for message sending 
void *rcv(); // for message receiving


/* Global variable definitions */

unsigned char rcv_msg[100], snd_msg[100];
int socket_fd, sock_fd_new, backlog = 10;

/* function definitions */
 
int main(int argc, char *argv[])
{

	struct sockaddr_in socketaddr;

	int snd_thread, rcv_thread;

	pthread_t thread1, thread2;

	socklen_t length = sizeof(socketaddr);

	memset(&socketaddr, 0, sizeof(struct sockaddr_in));

	/* Create a new socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd == -1)
		perror("socket");

	/* Upload the structure value */
	socketaddr.sin_family = AF_INET; /* always AF_INET for Internet */
	socketaddr.sin_port   = htons(atoi(argv[1])); /* port number convert to byte oreder*/
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr); /* ip address store to the structure as a network byte order */

	/* Bind with local address */
	if(bind(socket_fd,(struct sockaddr *)&socketaddr,length) == -1) 
		perror("bind");

	/* listening for the client */
	if(listen(socket_fd,backlog) == -1)
		perror("listen");

	/* accept the client with new file descriptor */
	sock_fd_new = accept(socket_fd, NULL, NULL);
	
	if(sock_fd_new == -1)
		perror("accept");

	/* receive the notification from client */
	recv(sock_fd_new, rcv_msg, 100, 0);
	printf("%s\n",rcv_msg);

	/* chat with client, until getting an exit message from client */
	while(1)
	{
		snd_thread = pthread_create(&thread1, NULL, snd, NULL); /* for send function*/

		rcv_thread = pthread_create(&thread2, NULL, rcv, NULL); /* for receive function */

		if(strcmp(rcv_msg,"exit")==0)
			exit (0); /* exit from the loop */
	}
	
	close(sock_fd_new); // close the sock_fd_new

	close(socket_fd);   // close the socket_fd
}

void *rcv()
{	
	recv(sock_fd_new,rcv_msg, 100,0); /* receive the messages */
	printf("%s\n",rcv_msg);		
}


void *snd()
{
	scanf("%[^\n]%*c",snd_msg);
	send(sock_fd_new, snd_msg, strlen(snd_msg)+1,0); /* send the messages */
}
