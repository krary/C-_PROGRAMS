#include "library.h"

void init_data(Host *h){
//================================================================================================
	h->hints.ai_family = AF_UNSPEC; //WHATEVER AF_INIET OR IF_INET_6
	h->hints.ai_socktype = SOCK_STREAM; //DEFINITION OF TYPE OF SOCKET (SOCKET STREAM OR DATAGRAM)
	h->hints.ai_flags = AI_PASSIVE; //FILL THE IP FOR MI PLEASE 
//================================================================================================

	if((h->status = getaddrinfo(NULL,"3940",&h->hints,&h->servinfo)) != 0){
		fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(h->status));
		exit(1);}
}

void show_data(Host *h){
	struct addrinfo *p;
	for(p = h->servinfo;p != NULL;p= p->ai_next){
		void *addr_ptr;
		char *ipver;
		if(p->ai_family == AF_INET){
			struct sockaddr_in *addr_in = (struct sockaddr_in*)p->ai_addr;
			addr_ptr = &(addr_in->sin_addr);
			ipver = "IPV4";}
	else{
struct sockaddr_in6 *addr_in = (struct sockaddr_in6*)p->ai_addr;
addr_ptr = &(addr_in->sin6_addr);
			ipver = "IPV6";        
		}
		inet_ntop(p->ai_family,addr_ptr,h->info_show,sizeof(h->info_show));
         
		printf("%s %s \n",ipver,h->info_show);}}


void init_socket(Host *h){
	h->file_descriptor_socket = socket(
		h->servinfo->ai_family,
		h->servinfo->ai_socktype,
		h->servinfo->ai_protocol);
	if(h->file_descriptor_socket == -1){
		perror("socket");
		return;}
}


void init_bind(Host *h){
	if(bind(h->file_descriptor_socket,
	h->servinfo->ai_addr,
	h->servinfo->ai_addrlen) == -1){
		perror("bind");
		return;} 
	
}


void init_listen(Host *h){
	listen(h->file_descriptor_socket,5);
	printf("LISTEN INIT CORRECT\n");}


void init_accept(Host *h) {
    h->size_of_there_struct = sizeof(h->there_struct);
	h->fd_socket_connection = accept(
	    h->file_descriptor_socket,
		(struct sockaddr*)&h->there_struct,
		&h->size_of_there_struct);
	
}


void init_send(Host *h){
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"Hi from here!!!");

	int status_respond = send(h->fd_socket_connection,buffer,strlen(buffer),0);
}
void init_recv(Host *h){
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	int num_recbyte=recv(
			h->file_descriptor_socket,
			buffer,sizeof(buffer),
			0);
   if(num_recbyte > 0){
	printf("[cliente] %s\n",buffer);}
}
