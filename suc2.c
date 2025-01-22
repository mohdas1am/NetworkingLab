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
		sendto(sockfc,NULL,NULL,0,(struct sockaddr *)&saddr,sizeof(saddr));
		char msg[100];
		recvfrom(sockfc,msg,sizeof(msg),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Server send reveresed string: %s\n",msg);
		close(sockfc);
	}
}
