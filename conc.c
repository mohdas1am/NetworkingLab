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
			int pid;
			recv(sockfc,&pid,sizeof(pid),0);
			printf("Pid:%d\n",pid);
			char name[100];
			printf("Filename: ");
			gets(name);
			send(sockfc,name,sizeof(name),0);
			FILE *fp=fopen("recvFile.txt","wb");
			if(fp){
				printf("Receiving file\n");
				char msg[1024];
				ssize_t byteRecv;
				while((byteRecv=recv(sockfc,msg,sizeof(msg),0))>0){
					fwrite(msg,1,byteRecv,fp);
				}fclose(fp);
				printf("File saved as recvFile.txt \n");
				char ch;
				FILE *fp=fopen("recvFile.txt","r");
				while((ch=fgetc(fp))!=EOF){
					printf("%c",ch);
				}fclose(fp);
			}else{
				printf("Error in file creation\n");
			}
		}
	}
}
