#include "library.h"


int main(){

Host *host_ = calloc(1,sizeof (Host));

init_data(host_);




    if(host_->servinfo != NULL) freeaddrinfo(host_->servinfo);
    free(host_);
	return 0;
}
