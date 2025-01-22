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
			printf("Connected to server\n");
			char toSend[100];
			printf("Enter string from client to send to Server: ");
			gets(toSend);
			int len=strlen(toSend);
			len=htonl(len);
			if(send(clientSocket,&len,sizeof(len),0)<0){
				printf("Can't send length to server\n");
				return;
			}else{
				printf("String len send\n");
				if(send(clientSocket,toSend,sizeof(toSend),0)<0){
					printf("Can't send string to server\n");
					return;
				}else{
					printf("String send\n connection terminating");
					close(clientSocket);
				}
			}
		}
	}
}
