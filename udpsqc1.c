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
		printf("Client 1 connected\n");
		int n;
		printf("Enter number: ");
		scanf("%d",&n);
		n=htonl(n);
		printf("Sending number to server\n");
		sendto(sockfc,&n,sizeof(n),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Closing connection\n");
		close(sockfc);
	}
}
