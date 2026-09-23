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
