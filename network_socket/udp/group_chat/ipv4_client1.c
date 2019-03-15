/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 22-feb-2019           */
/* Filename	: ipv4_client.c         */
/* Description	: socket sample program */
/****************************************/

/* Included header file */

#include "ipv4_client.h"

void *snd_fun();
void *recv_fun();

/* Global variable definitions */

unsigned char str1[8192],str[8192];
unsigned char ptr[2],ptr1[2]="1";
struct sockaddr_in socketaddr,recvaddr;
socklen_t length = sizeof(struct sockaddr_in);
int soc_ket,key;

/* function definitions */
 
int main(int argc,char *argv[])
{
	int detach,snd_thread,recv_thread,snd_t,rcv_t;

	pthread_t thread1,thread2,thread3, thread4;
	
	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

	//update the values to the struct
	socketaddr.sin_family =AF_INET;
	socketaddr.sin_port  = htons(atoi(argv[1]));
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr);
  
	sendto(soc_ket, "client 1 is online",20, 0,(struct sockaddr *)&socketaddr, sizeof(socketaddr));

	while(1)
	{
		recv_thread = pthread_create(&thread2,NULL,recv_fun,NULL);

		snd_thread = pthread_create(&thread1,NULL,snd_fun,NULL);
		
		detach = pthread_detach(thread1);
		detach = pthread_detach(thread2);
	}


	close(soc_ket);
}


void *snd_fun()
{
	scanf("%[^\n]%*c",str1);
	sendto(soc_ket, str1,strlen(str1)+1, 0,(struct sockaddr *)&socketaddr, sizeof(socketaddr));
}

void *recv_fun()
{

	recvfrom(soc_ket,str,8192,0,(struct sockaddr*)&recvaddr,&length);
	printf("%s\n",str);	
}
