#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

void main(){
	struct sockaddr_in saddr,caddr;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("Cannot create socket\n");
	}else{
		printf("Socket created with id %d\n",sockfd);
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=INADDR_ANY;
		
		if(bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr))<0){
			printf("Error in binding\n");
		}else{
			printf("Server binded\n");
			if(listen(sockfd,5)<0){
				printf("Error Listening\n");
			}else{
				int clen=sizeof(caddr);
				int isock=accept(sockfd,(struct sockaddr*)&caddr,&clen);
				if(isock==-1){
					printf("Error connecting to client1\n");
				}else{
					printf("Server is listening \n");
					float n;
					recv(isock,&n,sizeof(n),0);
					n=ntohl(n);
					printf("Client send %f to Server\n",n);
					n=pow(n,1.5);
					printf("Server increasing to 1.5 times it power: %f\n",n);
					printf("Server sending new value %f\n",n);
					send(isock,&n,sizeof(n),0);
					close(isock);
					close(sockfd);
				}
			}
		}
	}
}
