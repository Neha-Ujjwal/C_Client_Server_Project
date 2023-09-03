#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

char username[20];
char password[20];

int authenticate_user(int sockfd){
	int isAuthenticated=1;

        printf("enter username: ");
        scanf("%s",username);
        send(sockfd,username,sizeof(username),0);

        printf("enter password: ");
        scanf("%s",password);
        send(sockfd,password,sizeof(password),0);

        char res[50];
        recv(sockfd,res,sizeof(res),0);
        if(strcmp(res,"authentication")!=0){
		isAuthenticated=0;
                
        }

	return isAuthenticated;

}


int send_File(int client_socket){
        char fileName[50];
        printf("enter the file name you want to send : ");
        scanf("%s",&fileName);
        FILE *file=fopen(fileName,"rb");
        if(!file){
                perror("error in opening file");
                return 0;
        }

        char buffer[4096];
        size_t bytes_read;
        while((bytes_read=fread(buffer,1,sizeof(buffer),file))>0){
                send(client_socket,buffer,bytes_read,0);
        }
        fclose(file);
        return 1;
}


int main(){

	//step1:creating client socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket creation failed \n");
		exit(1);
	}else{
		printf("socket created successfully\n");
	}

	//step2:assigning IP,port to client socket
	struct sockaddr_in client_addr;

	memset(&client_addr,0,sizeof(client_addr));

	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        client_addr.sin_port=htons(8080);
	
	

	//step3:connecting with server
	if(connect(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr))!=0){
                exit(1);
        }
	
	int isAuthenticated=authenticate_user(sockfd);

	if(isAuthenticated==0){
		printf("\n authentication fails!! Try again with correct username and password \n \n ");
	}else{
	


         printf("connection created with server successfully..!!!!\n");
        
	
	 // file transfer 

	int fileToBeSent=0;
	char isFile[50];
	printf("do you want to send file to server?(yes/no)");
	scanf("%s",&isFile);
	

	if(strcmp(isFile,"yes")==0 || strcmp(isFile,"y")==0 || strcmp(isFile,"1")==0){
		fileToBeSent=1;
	}

	if(fileToBeSent==1){

		char header[]="file";
		send(sockfd,header,strlen(header),0);
		if(send_File(sockfd)==1){
			printf("file sent successFully \n");
		}else{
			printf("file sending failed \n");
		}
	
	}else{

	
	
		char buffer[1024];

		bzero(buffer,1024);

		char str[]="hello this is ";
		strcat(str,username);
		strcpy(buffer,str);
		printf("Client : %s \n",buffer);
		send(sockfd,buffer,strlen(buffer),0);

		bzero(buffer,1024);
		recv(sockfd,buffer,sizeof(buffer),0);
		printf("Server : %s\n",buffer);
	}

	close(sockfd);

	printf("disconnected from the server \n");

}
	return 0;



}
