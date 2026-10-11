#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct{

	int fd_socket;
	int getaddrinfo_status;
	struct addrinfo hints;
	struct addrinfo *servinfo;
}Host;

void init_socket(Host *);

#endif 
