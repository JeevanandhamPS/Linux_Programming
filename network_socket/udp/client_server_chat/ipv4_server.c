/*****************************************/
/* Author	: Jeevanandham.P.S       */
/* Date		: 22-feb-2019            */
/* Filename	: ipv4_server.c          */
/* Description	: server chat with client*/
/*****************************************/

/* Included header file */

#include "ipv4_server.h"

/* function prototypes */
void *send_fun();
void *recv_fun();


/* Global variable definitions */

struct sockaddr_in socketaddr;	//IPv4 socket details INET
unsigned char str1[8192],str[8192]; 
socklen_t length = sizeof(struct sockaddr_in); // socklen_t length..
int soc_ket;


/* function definitions */
 
int main(int argc,char *argv[])
{
	//variables for thread purpose..
	int snd_thread, recv_thread,detach,thread_join;
	pthread_t thread1,thread2;


	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

	//update the values to the struct
	socketaddr.sin_family =AF_INET;	//address family (AF_INET) for IPv4
	socketaddr.sin_port  = htons(atoi(argv[1])); // htons returns host_uint16 convert to network byte order
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr); //inet_pton() function converts the presentation string contained in src_str into a	binary IP address in network byte order...


	//bind the socket
	bind(soc_ket,(struct sockaddr *)&socketaddr,sizeof(socketaddr));

	//receive the notification for server from client, when the client as connect..
	recvfrom(soc_ket, str1,100, 0,(struct sockaddr *)&socketaddr, &length);
	//print the message..
	printf("%s\n",str1);
  
	//continue process...
	while(1)
	{
		//create a thread for message sending purpose... thread function call as without argument..
		snd_thread = pthread_create(&thread1,NULL,send_fun,NULL);

		//create a thread for message receiving purpose... thread function call as without argument..
		recv_thread = pthread_create(&thread2,NULL,recv_fun,NULL);

		//detach the threads...
		detach = pthread_detach(thread1); //thread1 detached

		detach = pthread_detach(thread2); //thread2 detached
	}
	

	//close the socket
	close(soc_ket); //socket as closed..
}

void *send_fun()
{
	//Get a message and send to other end..
	scanf("%[^\n]%*c",str); // scanf get the sting without newline ,newline end of the msg..

	//send the message to next end..
	sendto(soc_ket,str,strlen(str)+1,0,(struct sockaddr *)&socketaddr,sizeof(socketaddr));
}

void *recv_fun()
{
	//receive the message from other end and print it 
	recvfrom(soc_ket, str1,8192, 0,(struct sockaddr *)&socketaddr, &length);
	printf("%s\n",str1);
}
