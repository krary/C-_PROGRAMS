#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct{
		int status;
		struct addrinfo hints;   //OUR STRUCT WITH THE DATA THE CONNECTION THAT WE WANT TO MAKE
		struct addrinfo  *servinfo;  //WILL POINT TO THE RESULTS
		char info_show[INET6_ADDRSTRLEN];
	
}Host;


void init_data(Host*);

#endif
