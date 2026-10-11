#include "library.h"

void init_socket(Host *h){


	//DEFINIENDO FAMILY SOCKTYPE FLAGS...
	h->hints.ai_family = AF_UNSPEC;
	h->hints.ai_socktype = SOCK_STREAM;
	h->hints.ai_flags = 0;

	
	if((h->getaddrinfo_status = getaddrinfo("127.0.0.1","3940",&h->hints,&h->servinfo)) != 0){
		printf("SE HA PRODUCIDO UN ERROR \n");
		return;}
	if((h->fd_socket = socket(h->servinfo->ai_family,h->servinfo->ai_socktype,h->servinfo->ai_protocol)) == -1){
		printf("SE HA PRODUCIDO UN ERRO EN LA FUNCION SOCKET\n");
		return;}

	if((connect(h->fd_socket,h->servinfo->ai_addr,h->servinfo->ai_addrlen)) == -1){
		perror("connect");
		return;}

	char buffer[1024];
	memset(buffer,0,sizeof(buffer));

	int byte_recv = recv(h->fd_socket,buffer,sizeof(buffer)-1,0);
	if(byte_recv > 0){
		printf("BUFFER: %s\n",buffer);
	}

	
}
