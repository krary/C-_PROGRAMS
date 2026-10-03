#include "library.h"


int main(){

printf("VALUE OF INET_ADDRSTRLEN : %d\n",INET_ADDRSTRLEN);


PCap_info *p_cap = calloc(1,sizeof(PCap_info));
Protocols *protocols = calloc(1,sizeof(Protocols));

open_interface(p_cap);
capture_packet(p_cap);
reading_packet_ascii(p_cap);
init_struct_ethernet(p_cap);
reading_packet_ethernet_MAC(p_cap);
reading_packet_ethernet_type(p_cap);
init_struct_iphdr(p_cap);
reading_packet_iphdr(p_cap);

init_struct_Protocols(protocols,p_cap);


pcap_close(p_cap->handle);
if(p_cap != NULL)free(p_cap);
	return 0;
}
