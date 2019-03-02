/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 01-mar-2019           */
/* Filename	: tcp_client.c          */
/* Description	: private chat          */
/****************************************/

/* Included header file */

#include "tcp_client.h"


void *snd(); // for message send
void *rcv(); // for message receive

/* Global variable definitions */

int socket_fd, sock_fd_new, backlog = 10;
unsigned char snd_msg[100], rcv_msg[100];

/* function definitions */
 
int main(int argc, char *argv[])
{

	struct sockaddr_in socketaddr;
	
	int snd_thread, rcv_thread;

	pthread_t thread1, thread2;

	memset(&socketaddr, 0, sizeof(struct sockaddr_in));

	/* Create a new Socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd == -1)
		perror("socket");

	/* Upload the structure value */
	socketaddr.sin_family = AF_INET; /* always AF_INET for internet */
	socketaddr.sin_port   = htons(atoi(argv[1])); /* port number */
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr); /* ip address store to the structure as a network byte order */

	/* connect with the server */
	if(connect(socket_fd,(struct sockaddr *)&socketaddr,sizeof(struct sockaddr_in)) == -1)
		perror("connect");

	/* send a notification while connecting */
	send(socket_fd, "I am in online", 20,0);

	/* chat with server,until send a exit */
	while(1)
	{
		rcv_thread = pthread_create(&thread1, NULL, rcv, NULL); /* for receive function*/

		snd_thread = pthread_create(&thread2, NULL, snd, NULL); /* for sending function */

		if(strcmp(snd_msg,"exit")==0) /* exit from the loop*/
			exit (0);
	}

	close(socket_fd); /* close the socket */
}

void *snd()
{
	scanf("%[^\n]%*c",snd_msg);
	send(socket_fd, snd_msg, strlen(snd_msg)+1,0); /* send a messsage */
}

void *rcv()
{
	recv(socket_fd,rcv_msg,100,0);  /* receive the message */
	printf("%s\n",rcv_msg);
}
