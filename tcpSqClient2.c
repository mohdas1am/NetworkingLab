#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
	int sockfc=socket(AF_INET,SOCK_STREAM,0);
	if(sockfc==-1){
		printf("Error socket creation\n");
	}else{
		printf("Socket created by client 2 with id %d\n",sockfc);
		struct sockaddr_in saddr;
		saddr.sin_family=AF_INET;
		saddr.sin_port=htons(8080);
		saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		  if(connect(sockfc,(struct sockaddr *)&saddr,sizeof(saddr))<0){
			    printf("Can't connect to server\n");
		  }else{
			  printf("Client 2 connected to server\n");
			  int n;
			  send(sockfc,&n,sizeof(n),0);
			  printf("Squared number from server is %d\n");
			  printf("Closing connection with server\n");
		  }
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
