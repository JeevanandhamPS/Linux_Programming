/****************************************/
/* Author	: Jeevanandham.P.S      */
/* Date		: 21-feb-2019           */
/* Filename	: ipv4_server.c         */
/* Description	: IPV4 socket program   */
/****************************************/

/* Included header file */

#include "ipv4_server.h"

/* Global variable definitions */


/* function definitions */
 
int main()
{
	int soc_ket;
	struct sockaddr_in socketaddr;
	unsigned char str1[200];

	unsigned char ip_addr[] = "192.168.43.208";
	socklen_t length = sizeof(struct sockaddr_in);

	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

	memset(&socketaddr, 0, sizeof(struct sockaddr_in));
	
	//update the values to the struct
	socketaddr.sin_family =AF_INET;
	socketaddr.sin_port  = htons(8080);
	unsigned int ip = inet_pton(AF_INET,ip_addr,&socketaddr.sin_addr);
	//bind the socket
	bind(soc_ket,(struct sockaddr *)&socketaddr,sizeof(socketaddr));
	perror("bind");
  
	//receive a msg from client..
	recvfrom(soc_ket, str1,100, 0,(struct sockaddr *)&socketaddr, &length);
	perror("sendto");
	
	printf("%s\n",str1);

	close(soc_ket);
}
