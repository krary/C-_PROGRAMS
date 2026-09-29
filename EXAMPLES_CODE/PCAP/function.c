#include "library.h"


// ABRIR LA INTERFAZ 



                         /*open_interface*/
//===============================================================================
void open_interface(PCap_info* p){
	p->handle = pcap_open_live("wlxd8448953edc3",BUFSIZ,1,1000,p->error_buffer);
	if(p->handle==NULL){printf("ERROR %s\n",p->error_buffer);return;}

	printf("[EXIT] THE PROGRAM HAS CONNECT WITH THE KERNEL\n");
	
}
//================================================================================




                         /*capture_packet*/
//===================================================================================
void capture_packet(PCap_info *p){
	p->packet = pcap_next(p->handle,&p->header);
	if(p->packet == NULL){
		printf("THE PROGRMA CANNOT CAPTURE ANY PACKET PLEASE TRY LATTER...\n");return ;}
	else{
		printf("[+]NUMERO DE BYTE CAPTURADOS : %d\n",p->header.caplen);
		printf("[+]NUMERO REAL DE BYTES EN EL CABLE : %d\n",p->header.len);


	for(size_t x = 0; x < p->header.caplen; x++){
		printf("%02X ",p->packet[x]);
		if((x + 1) % 16 == 0)printf("\n");}}
printf("\n");}

//=====================================================================================



                    /*reading_packet_ascii*/
//=====================================================================================
void reading_packet_ascii(PCap_info *p){
	for(size_t x = 0; x < p->header.caplen;x++){
		u_char c = p->packet[x];
		if(isprint(c)){
			printf("%c",c);}
		else{
			printf(".");
		}
	}
printf("\n");
}




       				/*ESTRUCTURA Ethernet*/
//**************************************************************************************
void init_struct_ethernet(PCap_info *p){
	p->ether = (struct ether_header*)p->packet;}
//======================================================================================





//========================Reading info from the struct ether_header===================================
void reading_packet_ethernet_MAC(PCap_info *p){
   if(p == NULL){printf("Cann not read the Struct PCap plea check noch einmal...\n");return;}
    printf("MAC DESTINO: [");
	for(size_t x = 0; x < 6;++x){printf("%02X:",p->ether->ether_dhost[x]);}
    printf("]\n");


    printf("MAC ORIGEN: [");
	for(size_t x = 0; x < 6;++x){printf("%02X:",p->ether->ether_shost[x]);}
    printf("]\n");}
//*******************************************************************************************





//========================Reading info from the struct ether_header===================================
void reading_packet_ethernet_type(PCap_info *p){
    printf("VALUE OF ether_type  BEFORE TO CALL THE FUNCTION nthos [%04X]\n",p->ether->ether_type);
	uint16_t type = ntohs(p->ether->ether_type);
	printf("VALUE OF ether_type  AFTER TO CALL THE FUNCTION nthos [%04X]\n",type);



	switch(type){
		case ETHERTYPE_ARP:  printf("[ARP]\n"); break;
		case ETHERTYPE_IP:   printf("[IP]\n"); break;
		case ETHERTYPE_IPV6: printf("[IPV6]\n"); break;
		default            : printf("[OTHER TYPE]\n"); break;
			
	}
	
}
//*********************************************************************************************************




void init_struct_iphdr(PCap_info *p){
    if((ntohs(p->ether->ether_type)) == ETHERTYPE_IP){

    	p->ip_hdr = (struct iphdr*)(p->packet + sizeof(struct ether_header));
    	
	}
}
