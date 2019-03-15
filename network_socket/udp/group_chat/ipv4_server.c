/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 22-feb-2019           */
/* Filename	: ipv4_server.c         */
/* Description	: IPV4 socket program   */
/****************************************/

/* Included header file */

#include "ipv4_server.h"

void *send_fun();
void *recv_fun();

/* Global variable definitions */

struct sockaddr_in socketaddr,recvaddr;
struct sockaddr_in *client_details[100];

unsigned char str1[8192], str[8192],cln_addr[256];
unsigned int num = 0,sig;
socklen_t length = sizeof(struct sockaddr_in);
int soc_ket;

int snd_thread, recv_thread, detach;
pthread_t thread1, thread2;

static pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER; // mutex should initialize as a static

/* function definitions */
 
int main(int argc,char *argv[])
{
	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

	memset(&socketaddr, 0, sizeof(struct sockaddr_in));
	
	//update the values to the struct
	socketaddr.sin_family =AF_INET;
	socketaddr.sin_port  = htons(atoi(argv[1]));
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr);

	//bind the socket
	bind(soc_ket,(struct sockaddr *)&socketaddr,sizeof(socketaddr));
	perror("bind");

	while(1)
	{
		snd_thread = pthread_create(&thread1,NULL,send_fun,NULL);

		recv_thread = pthread_create(&thread2,NULL,recv_fun,NULL);

		detach = pthread_detach(thread1);
		detach = pthread_detach(thread2);		
	}
	close(soc_ket);
}

void *send_fun()
{
	int mut,i;
		
	scanf("%[^\n]%*c",str);

	for(i=0; i<num; i++)
	{
		mut = pthread_mutex_lock(&mutx);
	
		sendto(soc_ket,str,strlen(str)+1,0,(struct sockaddr *)client_details[i],sizeof(socketaddr));
		
		mut = pthread_mutex_unlock(&mutx);
	}
}

void *recv_fun()
{
	int count,mut,i=0;
	recvfrom(soc_ket, str1,8192, 0,(struct sockaddr *)&recvaddr, &length);
	printf("%s\n",str1);

	if(strcmp(str1,"I am in online")==0)
        {
		client_details[num] = &recvaddr;
		num++;
	}

	sig = recvaddr.sin_addr.s_addr;

	for(i=0; i<num; i++)
	{
		if( sig != client_details[i]->sin_addr.s_addr)
		{
			mut = pthread_mutex_lock( &mutx );

			sendto(soc_ket,str1,strlen(str1)+1,0,(struct sockaddr *)client_details[i],sizeof(socketaddr));

			inet_ntop(AF_INET, &client_details[i]->sin_addr.s_addr, cln_addr, length);
			printf("%s\n",cln_addr);

			mut = pthread_mutex_unlock( &mutx );
		}
	}
}
