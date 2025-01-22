#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void main(){
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in saddr,caddr;
	char rev[100];
	char s[100];
	int len;
	if(sockfd==-1){
		printf("Error in socket creation\n");
	}else{
		printf("Socket created 1 with socketId: %d\n",sockfd);
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		saddr.sin_port=htons(8080);
	
		int b=bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
		if(b==0){
			printf("Binded 1\n");
			if(listen(sockfd,5)<0){
				printf("Error listening 1\n");
			}int clen=sizeof(caddr);
			int isock=accept(sockfd,(struct sockaddr *)&caddr,&clen);
			if(isock<0){
				printf("Connection not established\n");
			}else{
				printf("Connected to client 1\n");
				if(recv(isock,&len,sizeof(len),0)<0){
					printf("Can't receive len from client\n");
					return;
				}else{
					len=ntohl(len);
					if(recv(isock,s,len,0)<0){
						printf("Can't receive string from client\n");
						return;
					}else{
						s[len]='\0';
						printf("String received from client: %s\n",s);
						for(int i=0;i<len;i++){
								rev[i]=s[len-i-1];
							}rev[len]='\0';
						printf("Reversed string is %s\n",rev);
						close(isock);
						isock=accept(sockfd,(struct sockaddr *)&caddr,&clen);
						if(isock<0){
							printf("Cant connect to client 2\n");
							return;
						}else{
							if(send(isock,rev,len,0)<0){
								printf("String not send to client2:\n");
								return;
							}else{
								printf("String send to client2:\n");
								close(isock);
								close(sockfd);
							}
						}
					}
				}
				
			}
		}
		else{
			printf("Error binding\n");
		}
	}
}
