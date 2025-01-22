#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
	struct sockaddr_in saddr;
	int clientSocket=socket(AF_INET,SOCK_STREAM,0);
	if(clientSocket==1){
		printf("Error socket creation");
	}else{
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		saddr.sin_port=htons(8080);
		int con=connect(clientSocket,(struct sockaddr *)&saddr,sizeof(saddr));
		if(con==0){
			printf("Connected\n");
			char rev[10];
			if(recv(clientSocket,rev,sizeof(rev),0)<0){
				printf("Client 2 can't get from server");
			}else{
				printf("Reversed string from server :%s \n",rev);
				close(clientSocket);
			}
		}
	}
}
