#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void main(){
	struct sockaddr_in saddr,caddr;
	int clen=sizeof(caddr);
	char msg[100]="TIME REQUEST";
	int sockfc=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfc<0){
		printf("Error\n");
	}else{
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=INADDR_ANY;
		saddr.sin_port=htons(8080);
		sendto(sockfc,msg,sizeof(msg),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Sending time request\n");
		recvfrom(sockfc,msg,sizeof(msg),0,(struct sockaddr *)&saddr,sizeof(saddr));
		printf("Time from server:%s",msg);
		close(sockfc);
	}		
}
