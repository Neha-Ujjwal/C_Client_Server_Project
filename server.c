#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

struct User{
	char username[50];
	char password[50];
};

struct User users[]={
	{"user1","pass1"},
	{"user2","pass2"},
	{"user3","pass3"}
};

int num_users=sizeof(users)/sizeof(users[0]);

int authenticate_user(int client_sock){
            	char username[20];
                char password[20];

                recv(client_sock,username,sizeof(username),0);
                recv(client_sock,password,sizeof(password),0);

                int isAuthenticated=0;

                for(int i=0;i<sizeof(users)/sizeof(users[0]);i++){
                        if(strcmp(username,users[i].username)==0 &&
                        strcmp(password,users[i].password)==0){
                                isAuthenticated=1;
                                break;
                        }
                }

               if(isAuthenticated){
                 //       printf("connected \n");
                       send(client_sock,"authentication",sizeof("authentication"),0);
               }else{
                       send(client_sock,"fail",sizeof("fail"),0);
                }
	return isAuthenticated;
}

int receive_File(int client_sock){
	FILE *file=fopen("received_file.txt","wb");
	if(!file){
		perror("file opening failed");
		return 1;
	}

	char buffer[4096];
	ssize_t bytes_received;
	while((bytes_received=recv(client_sock,buffer,sizeof(buffer),0))>0){
		fwrite(buffer,1,bytes_received,file);
	}

	fclose(file);
	return 0;
}





int main(){

	int sockfd;
	 struct sockaddr_in client_addr,server_addr;
        char buffer[1024];

	
	printf("***************Welcome to TCP Client-server program ****************\n\n");
	

	//step1->creating socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("error in creating socket...\n ");
		exit(1);
	}else{
		printf("Socket created successfully!!!!!!\n");
	}

	//struct sockaddr_in server_addr;


	

	//step 2: assigning port number,IP to socket
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	//server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(8080);

	if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("binding failed.... \n");
		close(sockfd);
		exit(0);
	}else{
		printf("socket binded successfully\n");
	}



	//step3 : listining for any request

	if(listen(sockfd,5)<0){
		perror("listening failed..\n");
		exit(0);
	}else{
		printf("server listening .... \n");
	}
	

	


	while(1){


		//creating client socket
		socklen_t addr_size=sizeof(client_addr);
		int client_sock=accept(sockfd,(struct sockaddr*)&client_addr,&addr_size);
	

		//validating user
		
		int isAuthenticated=authenticate_user(client_sock);
		
		if(isAuthenticated==0){
			printf("\n authentication failed !!! this client dont have any account \n\n");
			

		}else{
		  	printf("client connected!!!!!!!!! \n");
			
			//file transfer
			char header[13];
			ssize_t receivedText=recv(client_sock,header,sizeof(header),0);
			header[receivedText]='\0';

			if(strcmp(header,"file")==0){
			   	if(receive_File(client_sock)==0){
					printf("file received successfully \n");
				}
				else{
					printf("error in receiving the file \n");
				}
			}else{
				bzero(buffer,1024);
				recv(client_sock,buffer,sizeof(buffer),0);
				printf("Client : %s\n",buffer);
				
			
				bzero(buffer,1024);
				strcpy(buffer,"Hi this is server . Have a nice day!!!!!!\n");

				printf("Server : %s \n",buffer);
				send(client_sock,buffer,strlen(buffer),0);
			}

			close(client_sock);
			printf("client disconnected\n \n ");
            	}
	}
	return 0;
}
