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
					char fname[100];
					recv(isock,fname,sizeof(fname),0);
					printf("Client asked %s\n",fname);
					FILE *fp=fopen(fname,"rb");
					if(fp){
						char buffer[1024];
						size_t bytesRead;
						printf("Sending file to client\n");
						while((bytesRead=fread(buffer,1,sizeof(buffer),fp))>0){
							send(isock,buffer,sizeof(buffer),0);
						}fclose(fp);
					printf("File sent successfully\n");
					}else{
						printf("No such file\n");
						char msg[]="No such file available";
						send(isock,msg,sizeof(msg),0);
					}
					close(isock);
					close(sockfd);
				}
				
			}
		}
	}
}
