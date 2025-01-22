#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
	int sockfc = socket(AF_INET, SOCK_DGRAM, 0);
    	if (sockfc == -1) {
        	printf("Socket not created\n");
        	return 1;
    	}else{
    		struct sockaddr_in saddr;
    		saddr.sin_family = AF_INET;
    		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    		saddr.sin_port = htons(8080);
    		char msg[100],rep[100];
    		printf("Enter message: ");
		gets(msg);
		printf("Sending message: %s\n",msg);
		sendto(sockfc,msg,strlen(msg)+1,0,(struct sockaddr *)&saddr,sizeof(saddr));
		int clen=sizeof(saddr);
		recvfrom(sockfc,rep,sizeof(rep),0,(struct sockaddr *)&saddr,&clen);
		printf("Server send: %s\n",rep);
		close(sockfc);
    	}
}
