#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
	struct sockaddr_in saddr;
	int sockfc= socket(AF_INET,SOCK_DGRAM,0);
	if(sockfc==-1){
		printf("Error socket creation\n");
		return;
	}else{
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		saddr.sin_port=htons(8080);
		
		char msg[100];
		printf("Enter string\n");
		gets(msg);
		int n= strlen(msg);
		n=htonl(n);
		printf("Sending string length %d\n",n);
		sendto(sockfc,&n,sizeof(n),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Sending from client 1 to server the string: %s\n",msg);
		sendto(sockfc,msg,sizeof(msg),0,(struct sockaddr *)&saddr,sizeof(saddr));
		close(sockfc);
	}
}
