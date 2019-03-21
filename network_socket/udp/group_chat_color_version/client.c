/*****************************************/
/* Author	: Jeevanandham.P.S       */
/* Date		: 22-feb-2019            */
/* Filename	: ipv4_client.c          */
/* Description	: client chat with server*/
/*****************************************/

/* Included header file */

#include "client.h"

/* function prototypes */
void *snd_fun();
void *recv_fun();

/* Global variable definitions */

struct sockaddr_in socketaddr;	//IPv4 socket details..
socklen_t length = sizeof(struct sockaddr_in); //socklen_t...
int soc_ket,i;

/* receive msg with sender name */
struct rv
{
	char u_r[256];
	unsigned char str[8192];
};
struct rv rev;

/* send msg with name */
struct sd
{
	char s_r[256];
	unsigned char str1[8192];
};
struct sd snd = {"hii","I am in online"};

/* function definitions */
 
int main(int argc,char *argv[])
{
	//variables for thread purpose..
	int detach,snd_thread,recv_thread,thread_join;
	pthread_t thread1,thread2;

	 int status,i;
         struct stat details;
         struct passwd *usr_name;
         struct utsname os_detail;
 
         /* To get get a Operating system and kernal information by using uname s    ystem call */
         int call = uname(&os_detail); /* Information stored in utsname structure     variable os_detail */
 
         /* To get a system status */
         status = stat(".",&details); /* all information stored in details*/
 
         if(status == -1)
                 perror("stat");
 
         usr_name = getpwuid(details.st_uid); /* To get a user name by using user     id */
	 char *tem = usr_name->pw_name;
	
	 for(i=0; tem[i] != 0; i++)
		 snd.s_r[i] = tem[i];

	
	//open a new socket, with DGRAM type protocol
	soc_ket=socket(AF_INET,SOCK_DGRAM,0);
	perror("socket");

	//update the values to the struct
	socketaddr.sin_family =AF_INET; //address family (AF_INET) for IPv4
	socketaddr.sin_port  = htons(atoi(argv[1]));// htons returns host_uint16 convert to network byte order
	unsigned int ip = inet_pton(AF_INET,argv[2],&socketaddr.sin_addr);//inet_pton() function converts the presentation string contained in src_str into a	binary IP address in network byte order...
  
	//send a notification to the current server, when client get a connection that time, it send a message to the server..
	sendto(soc_ket, &snd,sizeof(snd), 0,(struct sockaddr *)&socketaddr, sizeof(socketaddr));
	while(1)
	{
		//create a thread for message receiving purpose... thread function call as without argument..
		recv_thread = pthread_create(&thread2,NULL,recv_fun,NULL);

		//create a thread for message sending purpose... thread function call as without argument..
		snd_thread = pthread_create(&thread1,NULL,snd_fun,NULL);
	
		//detach the threads..
		detach = pthread_detach(thread1); // detach the thread1
		detach = pthread_detach(thread2); // detach the thread2
	}

	//close the socket..
	close(soc_ket);	//socket as closed..
}


void *snd_fun()
{
	//Get a message and send to other end..
	scanf("%[^\n]%*c",snd.str1); // scanf get the sting without newline ,newline end of the msg..

	//send the message to next end..
	sendto(soc_ket, &snd,sizeof(snd), 0,(struct sockaddr *)&socketaddr, sizeof(socketaddr));
}

void *recv_fun()
{
	//receive the message from other end and print it 
	recvfrom(soc_ket,&rev,sizeof(rev),0,(struct sockaddr*)&socketaddr,&length);
	printf(GREEN"\t\t%s : "RESET,rev.u_r);	
	printf("%s\n",rev.str);	
}
