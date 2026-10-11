#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct{
		int status;
		int file_descriptor_socket;
		int fd_socket_connection;
		socklen_t size_of_there_struct;
		struct addrinfo hints;   //OUR STRUCT WITH THE DATA THE CONNECTION THAT WE WANT TO MAKE
		struct addrinfo  *servinfo;  //WILL POINT TO THE RESULTS
		struct sockaddr_storage there_struct;
		char info_show[INET6_ADDRSTRLEN];
	
}Host;


void init_data(Host*);
void show_data(Host*);
void init_socket(Host*);
void init_bind(Host*);
void init_listen(Host*);
void init_accept(Host*);
void init_send(Host*);

#endif
