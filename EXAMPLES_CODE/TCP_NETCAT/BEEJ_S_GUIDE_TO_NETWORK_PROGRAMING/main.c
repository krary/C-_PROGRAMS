#include "library.h"


int main(){

Host *host_ = calloc(1,sizeof (Host));

init_data(host_);
show_data(host_);
init_socket(host_);
init_bind(host_);
init_listen(host_);
init_accept(host_);
init_send(host_);
init_recv(host_);



    if(host_->servinfo != NULL) freeaddrinfo(host_->servinfo);
    free(host_);
	return 0;
}
