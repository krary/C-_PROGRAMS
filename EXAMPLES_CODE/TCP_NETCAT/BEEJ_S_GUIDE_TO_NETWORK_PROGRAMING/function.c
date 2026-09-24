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
		inet_ntop(p->ai_family,addr_ptr,h->info_show,sizeof(h->info_show));
         
		printf("%s %s \n",ipver,h->info_show);
	}
}
