#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in saddr,caddr;
	if(sockfd==-1){
		printf("NO socket created\n");
	}else{
		printf("Socket created with id %d\n",sockfd);
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=INADDR_ANY;
		if(bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr))<0){
			printf("Error binding\n");
		}else{
			printf("Binded\n Server Listening");
			int clen=sizeof(caddr);
			int n;
			recvfrom(sockfd,&n,sizeof(n),0,(struct sockaddr *)&caddr,&clen);
			n=htonl(n);
			printf("Client1 connected\n Client1 sent number %d\n",n);
			n*=n;
			printf("Squared to %d\n",n);
			printf("Removing connection with client1\nTrying to connect client 2\n");
			if(recvfrom(sockfd,NULL,NULL,0,(struct sockaddr *)&caddr,&clen)<0){
				printf("Can't connect to client 2\n");
			}else{
				printf("Connected to client 2\nSending squared number to client 2\n");
				sendto(sockfd,&n,sizeof(n),0,(struct sockaddr *)&caddr,clen);
				printf("Closing socket\n");
				close(sockfd);
			}
			
		}
	}
}
