#include "library.h"


int main(){

PCap_info *p_cap = calloc(1,sizeof(PCap_info));
open_interface(p_cap);
capture_packet(p_cap);
reading_packet_ascii(p_cap);




pcap_close(p_cap->handle);
if(p_cap != NULL)free(p_cap);
	return 0;
}
