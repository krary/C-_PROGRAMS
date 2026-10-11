#include "library.h"


int main(){
   Host *h = calloc(1,sizeof(Host));
  
   init_socket(h);

  
  
   
    if(h->servinfo !=NULL){
    	freeaddrinfo(h->servinfo);
    	free(h);
    }

	return 0;
}
