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
		struct sockaddr_in saddr,caddr,caddr2;
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=INADDR_ANY;
		saddr.sin_port=htons(8080);
		if(bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr))<0){
			printf("Error binding:\n");
			return;
		}else{
			printf("Bind successfull\n");
			printf("Server listening\n");
			int n;
			int clen=sizeof(caddr);
			char msg[100],rep[100];
			recvfrom(sockfd,&n,sizeof(n),0,(struct sockaddr *)&caddr,&clen);
			n=ntohl(n);
			recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&caddr,&clen);
			printf("Server received from client 1: %s\n",msg);
			for(int i=0;i<n;i++){
				rep[i]=msg[n-i-1];
			}rep[n]='\0';
			printf("Reversed string is %s\n",rep);
			recvfrom(sockfd,NULL,NULL,0,(struct sockaddr *)&caddr2,&clen);
			printf("Sending string ito client 2\n");
			sendto(sockfd,rep,sizeof(rep),0,(struct sockaddr *)&caddr2,clen);
			close(sockfd);
		}
	}
}
