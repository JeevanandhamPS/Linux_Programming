/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 21-feb-2019           */
/* Filename	: ipv4_client.c         */
/* Description	: socket sample program */
/****************************************/

/* Included header file */

#include "ipv4_client.h"

/* Global variable definitions */


/* function definitions */
 
int main(int argc, char *argv[])
{
	int soc_ket;
	struct sockaddr_in socketaddr;
	unsigned char str1[]="message from client by IPV4 SOCKET", str2[200];

	socklen_t length = sizeof(struct sockaddr_in);

	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

//	memset(&socketaddr, 0, sizeof(struct sockaddr_in));
	
	//update the values to the struct
	socketaddr.sin_family =AF_INET;
	socketaddr.sin_port  = htons(atoi(argv[1]));
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr);
  
	//send a msg to server..
	sendto(soc_ket, str1,strlen(str1)+1, 0,(struct sockaddr *)&socketaddr, sizeof(socketaddr));
	perror("sendto");	
	sleep(2);
	
	recvfrom(soc_ket, str2,100, 0,(struct sockaddr *)&socketaddr, &length);
	perror("recvfrom");

	printf("%s\n",str2);
	
	close(soc_ket);
}
