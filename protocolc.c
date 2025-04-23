#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void main(){
	int sockfc=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in saddr;
	
	if(sockfc<0){
		printf("Error socket creation\n");
	}else{
		printf("Socket created with id %d\n",sockfc);
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		int b=connect(sockfc,(struct sockaddr *)&saddr,sizeof(saddr));
		if(b<0){
			printf("Error connecting\n");
		}else{
			printf("Connected successfully\n");
			int i=0,rep;
			while(i<10){
				send(sockfc,&i,sizeof(i),0);
				recv(sockfc,&rep,sizeof(rep),0);
				if(rep==0){
					printf("Packet %d not acknowledged\n",i);
				}else{
					printf("Packet %d acknowledge\n",i);
					i++;
				}
			}
		}close(sockfc);
	}
}
