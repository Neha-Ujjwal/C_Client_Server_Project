# TCP Server-Client Program in C

## description
This project provides a hands-on understanding of creating a simple TCP server-client program using the C programming language. The primary objective is to illustrate the foundational concepts of client-server architecture and the communication process between them. In this model, a server offers services or resources to  clients. Clients initiate requests to the server, which processes these requests and responds with the necessary data.

## Goals

- Implementing a basic TCP client-server model in C.
- Exploring socket programming concepts to establish communication channels.
- Enhancing capabilities for file transfer between clients and server.
- Incorporating basic authentication mechanisms for secure interactions.

## Specification

### Server-Side Process

1. **Creating TCP Socket**: Use `create()` to initiate the creation of a TCP socket.
2. **Binding the Socket**: Employ `bind()` to associate the socket with the server's address.
3. **Listening for Clients**: Apply `listen()` to transition the server socket to a passive mode, awaiting client connections.
4. **Accepting Client Connections**: Use `accept()` to establish connections with clients, enabling data transfer.
   - The server waits, ready to receive client requests.

### Client-Side Process

1. **Creating TCP Socket**: Utilize `socket()` to generate a TCP socket.
2. **Connecting to the Server**: Employ `connect()` to establish a connection with the server.
   - The client is now ready to communicate.

3. **Closing the Connection**: Use `close()` to terminate the connection when communication is complete.


## design
![image](https://github.com/Neha-Ujjwal/C_project_demo/assets/104856137/8f48ff7e-88cb-4f36-b46f-66cf349f9195)




 
## Usage

Follow these steps to clone the repository, compile the server and client, and see them communicate with each other.

1. clone the repository : `https://github.com/Neha-Ujjwal/C_project_demo.git` 
2. Navigate to project folder: `cd C_project_demo`
3. compile the server file in current window : `gcc server.c -o server.o`
4. compile the client file in another window : `gcc client.c -o client.o`
5. Now run both the files using in their respective windows 
   `./server`  ,  `./client`

## Output
![image](https://github.com/Neha-Ujjwal/C_project_demo/assets/104856137/d927b459-fb4e-4843-8973-886698b15432)



