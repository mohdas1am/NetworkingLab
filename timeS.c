#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>



void main(){
	struct sockaddr_in saddr,caddr;
	int clen=sizeof(caddr);
	char msg[100],t[100];
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
		printf("Error\n");
	}else{
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=INADDR_ANY;
		saddr.sin_port=htons(8080);
		int b=bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
		if(b<0){
			printf("Error binding\n");
		}else{
			printf("Server listening\n");
			recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&caddr,&clen);
			printf("Client send : %s\n",msg);
			time_t now = time(NULL);
			snprintf(t, sizeof(t), "Server Time: %s", ctime(&now));
			printf("Sending time to client\n");
			sendto(sockfd,t,sizeof(t),0,(struct sockaddr *)&caddr,clen);
			close(sockfd);
		}
	}
}
