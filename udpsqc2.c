#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int sockfc=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in saddr,caddr;
	if(sockfc==-1){
		printf("NO socket created\n");
	}else{
		printf("Socket created with id %d\n",sockfc);
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=INADDR_ANY;
		sendto(sockfc,NULL,NULL,0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Client 2 connected\n");
		int n;
		recvfrom(sockfc,&n,sizeof(n),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Server sent square: %d\n",n);
		printf("Closing connection\n");
		close(sockfc);
	}
}
