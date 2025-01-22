#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
		printf("Error creating socket\n");
		return;
	}else{
		printf("Socket Created with id %d\n",sockfd);
		struct sockaddr_in saddr,caddr;
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=INADDR_ANY;
		saddr.sin_port=htons(8080);
		if(bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr))<0){
			printf("Error binding:\n");
			return;
		}else{
			printf("Bind successfull\n");
			printf("Server listening\n");
			int clen=sizeof(caddr);
			char msg[100],rep[100];
			recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&caddr,&clen);
			printf("Client send: %s\n",msg);
			printf("Enter reply: ");
			gets(rep);
			sendto(sockfd,rep,strlen(rep)+1,0,(struct sockaddr *)&caddr,clen);
			close(sockfd);
		}
	}
}
