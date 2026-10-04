#include "library.h"

static pcap_t *global_handler_state = NULL;
void my_callback_mutation(int signum){
	if(global_handler_state != NULL){
		printf("[**CERRANDO DE FORMA SEGURA EL PROGRAMA**\n]");
		pcap_breakloop(global_handler_state);}}


int main(){

printf("VALUE OF INET_ADDRSTRLEN : %d\n",INET_ADDRSTRLEN);


PCap_info *p_cap = calloc(1,sizeof(PCap_info));
Protocols *protocols = calloc(1,sizeof(Protocols));
p_cap->p = protocols;

signal(SIGINT,my_callback_mutation);

open_interface(p_cap);
if(p_cap->handle != NULL)global_handler_state = p_cap->handle;
start_capture_loop(p_cap,0);

pcap_close(p_cap->handle); //CERRANDO EL DESCRIPTOR DE ARCHIVOS..
if(p_cap != NULL)free(p_cap);
if(protocols != NULL)free(protocols);
	return 0;
}
