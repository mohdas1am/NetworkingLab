#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void main(){
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in saddr,caddr;
	
	if(sockfd<0){
		printf("Error socket creation\n");
	}else{
		printf("Socket created with id %d\n",sockfd);
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=INADDR_ANY;
		int b=bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
		if(b<0){
			printf("Error binding\n");
		}else{
			printf("Binded successfully\n");
			int clen=sizeof(caddr);
			if(listen(sockfd,5)<0){
				printf("Error listening\n");
			}else{
				printf("Server listening\n");
				int isock=accept(sockfd,(struct sockaddr *)&caddr,&clen);
				if(isock<0){
				printf("Error connecting to client\n");
				}else{
					printf("Server connected to client\n");
					int ack=1,nck=0,arrseq,i=0;
					while(i<10){
						recv(isock,&arrseq,sizeof(arrseq),0);
						if(rand()%3==0){
							printf("Packet %d lost\n",arrseq);
							send(isock,&nck,sizeof(nck),0);
						}else{
							printf("Packet %d received\n",arrseq);
							send(isock,&ack,sizeof(ack),0);
							i++;
						}sleep(3);
					}
				}close(isock);
			}close(sockfd);
		}
	}
}
