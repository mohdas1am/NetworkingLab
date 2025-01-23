#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int sockfc=socket(AF_INET,SOCK_STREAM,0);
	if(sockfc==-1){
		printf("Error socket creation\n");
	}else{
		printf("Socket created by client 1 with id %d\n",sockfc);
		struct sockaddr_in saddr;
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		if(connect(sockfc,(struct sockaddr *)&saddr,sizeof(saddr))<0){
			printf("Can't connect to server\n");
		}else{
			printf("Client 1 connected to server\n");
			float n,p;
			printf("Enter number: ");
			scanf("%f",&n);
			n=htonl(n);
			printf("Sending number to server\n");
			send(sockfc,&n,sizeof(n),0);
			recv(sockfc,&p,sizeof(p),0);
			printf("Server send increased number %f \n",p);
			close(sockfc);
		}
	}
}
