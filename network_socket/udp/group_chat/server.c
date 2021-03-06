/*********************************************/
/* Author	: Jeevanandham.P.S           */
/* Date		: 22-feb-2019                */
/* Filename	: server.c                   */
/* Description	: group chat serverprogram   */
/*********************************************/

/* Included header file */

#include "server.h"

void *send_fun();
void *recv_fun();

/* Global variable definitions */

int soc_ket,clnt;
struct sockaddr_in socketaddr, recvaddr;
struct sockaddr_in c_addr[100]; /* max 100 clients can join */

int snd_thread, recv_thread, detach;
pthread_t thread1, thread2;

unsigned char str[8192],str1[8192]; /* message length max 8192 characters */
unsigned int num = 0,per;

socklen_t length = sizeof(struct sockaddr_in);

struct sockaddr_in *client_addr1, *client_addr2;

/* function definitions */

int main(int argc, char *argv[])
{
	//open a new socket, with DGRAM type protocol
	soc_ket = socket(AF_INET, SOCK_DGRAM, 0);

	//socket creation failed, print the error message
	if(soc_ket == -1)
		perror("socket");
	
	//set the size 
	memset(&socketaddr, 0, sizeof(struct sockaddr_in));	

	//Update the values to the structure...
	socketaddr.sin_family = AF_INET; // family always AF_INET for internet
	socketaddr.sin_port   = htons(atoi(argv[1])); // convert port number to network byte order..
	unsigned int ip = inet_pton(AF_INET, argv[2], &socketaddr.sin_addr ); //store the ip address on network byte order.

	//bind the socket with the local address..
	if(bind(soc_ket, (struct sockaddr *)&socketaddr,sizeof(socketaddr)) == -1)
		perror("bind");

	// send and receive thread function	

	while(1)
	{
		//send function thread..
		snd_thread = pthread_create(&thread1, NULL, send_fun, NULL);

		//receive function thread..
		recv_thread = pthread_create(&thread2, NULL, recv_fun, NULL);

		//detach the thread1
		detach = pthread_detach(thread1);

		//detach the thread2
		detach = pthread_detach(thread2);
	}

	//close the socket
	close(soc_ket);
}

void *send_fun()
{
	int i;
	scanf("%[^\n]%*c",str);
	/* sending message to all clients */
	for(i=0;i<num;i++)
		//c_addr[] had the client structures..
		sendto(soc_ket, str, strlen(str)+1, 0, (struct sockaddr *)&c_addr[i], sizeof(socketaddr)); 
}

void *recv_fun()
{
	int i,valid;

	//receive a message
	recvfrom(soc_ket, str1, 8192, 0, (struct sockaddr *)&recvaddr, &length);
	printf("\t\t%s\n",str1);

	//store the client structure address
	if(num == 0) /* first client structure should be access the step */
	{
		c_addr[num] = recvaddr; //to assign the receive address to the structure member..
		num++;
	}

	else 
	{
		valid = 0;

		/* check whether the client already present or not, if already present ignore the structure storing steps */
		for(i=0; i<num; i++)
			if(c_addr[i].sin_addr.s_addr == recvaddr.sin_addr.s_addr)
				valid = 1;
		if(valid == 0)
		{
			c_addr[num] = recvaddr; //to assign the receive address to the structure member..
			num++;
		}
	}

	/* assign the received client ip to per, because sender no need to receive the same message */
	per = recvaddr.sin_addr.s_addr;

	for(i=0; i<num; i++)
	{
		/* this step will skip for sender */
		if(per != c_addr[i].sin_addr.s_addr)
		{
			/* Send a message to other all clients except sender */
			sendto(soc_ket, str1, strlen(str1)+1, 0, (struct sockaddr *)&c_addr[i], sizeof(recvaddr) );
		}
	}
}
