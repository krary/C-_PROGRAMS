#include "library.h"


int main(){


   struct iphdr *ip_hdr;
   struct tcphdr *tcp_hdr;

   init_ip(ip_hdr);
   init_tcp(tcp_hdr);



	return 0;
}
